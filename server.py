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

def getLastMessage():
    tg.get_chats().wait()
    history = tg.get_chat_history(environ["BLAKKIS_CHAT_ID"])
    history.wait()
    print(history.update["messages"][0]["content"]["text"]["text"])


@app.route('/', methods=['POST'])
def add_drink():
    data = request.get_json()
    amount = data.get('amount')
    percentage = data.get('percentage')
    print(amount + "cl " + percentage)
    tg.send_message(environ["BLAKKIS_CHAT_ID"], amount + "cl " + percentage + "%")
    time.sleep(1)
    getLastMessage()
    return "Thank you"


@app.route("/quit")
def quit():
    tg.stop()
    return "Bye Telegram"
