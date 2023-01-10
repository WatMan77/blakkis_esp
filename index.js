const dotenv = require('dotenv')
dotenv.config()

const { Client } = require('tdl')
const { TDLib } = require('tdl-tdlib-addon')

const client = new Client(new TDLib(process.env.LIB_PATH), {
  apiId: process.env.APP_ID, // Your api_id
  apiHash: process.env.APP_HASH // Your api_hash,
})

const main = async () => {
  await client.login()

  const result = await client.invoke({
    _: 'sendMessage',
    chat_id: process.env.BLAKKIS_CHAT_ID,
    input_message_content: {
      _: 'inputMessageText',
      text: {
        _: 'formattedText',
        text: '/kalja033'
      }
    }
  })

  console.log('Result?')
  console.log(result)

  // await client.close()

}

main().catch(console.error)
