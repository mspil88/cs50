import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# TODO: ADD LOGIC TO SAFE GUARD AGAINST SELLING MORE SHARES THAN INDIVIDUAL HAS, to check!
# TODO: ADD PERSONAL FEATURE


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    user_id = session['user_id']
    stocks = db.execute("SELECT stock, company, sum(shares) as shares FROM all_transactions where user_id = ? GROUP BY stock, company", user_id)
    print(stocks)
    print(type(stocks))

    grand_total = 0
    for i in stocks:
        stock, shares = i['stock'], int(i['shares'])
        print(stock)
        print(lookup(stock))
        price = lookup(stock)['price']
        total = price * shares
        i['price'] = round(price, 2)
        i['total'] = round(total, 2)
        grand_total += i['total']

    print(stocks)
    return render_template("index.html", stocks=stocks, grand_total=round(grand_total,2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        company = request.form.get("symbol")
        num_shares = int(request.form.get("shares"))
        try:
            value = lookup(company)
            company, price, symbol = value['name'], value['price'], value['symbol']
        except:
            return apology("must enter a valid symbol", 400)

        user_id = session['user_id']
        cash = db.execute("SELECT cash FROM users where id = ?", user_id)[0]['cash']
        txn_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        cost = num_shares*price

        if cost > cash:
            return apology("insufficient funds", 400)

        else:
            db.execute("INSERT INTO all_transactions (user_id, amount, stock, company, shares, datetime, direction) VALUES(?, ?, ?, ?, ?, ?, ?)", user_id, (-1)*cost, symbol, company, num_shares, txn_date, "bought")
            #update cash
            db.execute("UPDATE users SET cash = ? where id = ?", cash-cost, user_id)
            return render_template("index.html")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    history = db.execute("select stock, company, abs(shares) as shares, round(abs(amount),2) as amount, datetime, direction from all_transactions")
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        try:
            quote = request.form.get("quote")
            value = lookup(quote)
            company, price, symbol = value['name'], value['price'], value['symbol']

            return render_template("quoted.html", company=company, price=price, symbol=symbol)
        except TypeError:
            return apology("must enter a valid symbol", 400)

    else:
        return render_template("quote.html")

@app.route("/reset_password", methods=["GET", "POST"])
def reset_password():
    session.clear()
    if request.method == "POST":
        username = request.form.get("username")
        old_password = request.form.get("password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirm_new_password")

        check_exists = db.execute("SELECT * FROM users where username = ?", username)


        if not username:
            return apology("must specify a username", 400)

        elif not old_password:
            return apology("must specify password", 400)

        elif not new_password:
            return apology("must provide new password", 400)

        elif not confirmation:
            return apology("must confirm new password", 400)

        elif new_password != confirmation:
            return apology("passwords do not match", 400)

        elif not check_exists:
            return apology("username does not exist", 400)

        else:
            pw_hash = generate_password_hash(new_password)
            #check confirmation matches password
            db.execute("UPDATE users SET hash = ? where username = ?", pw_hash, username)
            db.execute("select * from users")
            return redirect("/login")
    else:
        return render_template("reset_password.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")


        check_exists = db.execute("SELECT * FROM users where username = ?", username)

        if not username:
            return apology("must specify a username", 400)

        elif not password:
            return apology("must specify a username", 400)

        elif not confirmation:
            return apology("must provide password confirmation", 400)

        elif password != confirmation:
            return apology("passwords do not match", 400)

        elif check_exists:
            return apology("username already exists", 400)

        else:
            pw_hash = generate_password_hash(password)
            #check confirmation matches password
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, pw_hash)
            db.execute("select * from users")
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session['user_id']

    if request.method == "POST":
        history = db.execute("select stock, company, abs(shares) as shares, round(abs(amount),2) as amount, datetime, direction from all_transactions")

        company = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares < 1:
            return apology("You must sell a positive amount", 403)

        for i in history:
            if i['stock'] == company:
                current_shares = i['shares']

        if shares > current_shares:
            return apology("You do not have enough shares", 403)


        value = lookup(company)
        price, symbol, company_name = value['price'], value['symbol'], value['name']
        txn_date = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        cash = db.execute("SELECT cash FROM users where id = ?", user_id)[0]['cash']
        #db.execute("INSERT INTO sales (user_id, stock, company, shares, return, datetime) VALUES(?, ?, ?, ?, ?, ?)", user_id, symbol, company, shares, shares*price, txn_date)
        db.execute("INSERT INTO all_transactions (user_id, amount, stock, company, shares, datetime, direction) VALUES(?, ?, ?, ?, ?, ?, ?)", user_id, shares*price, symbol, company_name, (-1)*shares, txn_date, "sell")
        db.execute("UPDATE users SET CASH = ? where id = ?", cash+(shares*price), user_id)
        return redirect("/")
    else:
        #use master table
        stocks = db.execute("SELECT DISTINCT stock from all_transactions where direction = 'bought'")


        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
