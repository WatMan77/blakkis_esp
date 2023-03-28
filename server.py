from flask import Flask, request
from os import environ
#from utils import setup_logging
from telegram.client import Telegram
from dotenv import load_dotenv
import time

load_dotenv()


tg = Telegram(
    api_id=environ["APP_ID"],
    api_hash=environ["APP_HASH"],
    phone=environ["PHONE_NUMBER"],
    database_encryption_key="Somerandomstring"
)

tg.login()

result = tg.get_chats()

result.wait()

if result.error:
    print(f'get chats error: {result.error_info}')
else:
    print(f'chats: {result.update}')

app = Flask(__name__)

chatId = environ["BLAKKIS_CHAT_ID"]

def getLastMessage():
    tg.get_chats().wait()
    history = tg.get_chat_history(chatId)
    history.wait()
    msg = history.update["messages"][0]["content"]["text"]["text"]
    print(msg)
    return msg

# This is to make sure you can add drinks with just the amount + cl + " " + percentage + %
# You need to add a drink using the menu and not with the "Oma" option
def firstTime(msg, amount, percentage):
    if "Mitä? Jos kaipaat apua käyttämiseen, kirjoita /help" in msg:
        tg.send_message(chatId, "/juoma")
        time.sleep(1)
        tg.send_message(chatId, "Oma")
        time.sleep(1)
        tg.send_message(chatId, percentage)
        time.sleep(1)
        tg.send_message(chatId, amount)


@app.route('/', methods=['POST'])
def add_drink():
    data = request.get_json()
    amount = data.get('amount')
    percentage = data.get('percentage')
    print(amount + "cl " + percentage)
    tg.send_message(chatId, amount + "cl " + percentage + "%")
    time.sleep(1)
    firstTime(getLastMessage(), amount, percentage)
    return "Thank you"


@app.route("/quit")
def quit():
    tg.stop()
    return "Bye Telegram"
