const dotenv = require('dotenv')
dotenv.config()

console.log('ENVS?')
//console.log(process.env.LIB_PATH)

const { Client } = require('tdl')
const { TDLib } = require('tdl-tdlib-addon')

const client = new Client(new TDLib(process.env.LIB_PATH), {
  apiId: process.env.APP_ID, // Your api_id
  apiHash: process.env.APP_HASH // Your api_hash,

})

client.login().then(x => {
  console.log(x)
})