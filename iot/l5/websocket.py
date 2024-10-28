import asyncio
import websockets

allowed = [[0x5A, 0x6C, 0x6B, 0x15], [0x12, 0x12, 0x12, 0x12]]

async def echo(websocket, path):
    async for message in websocket:
        m = list(map(int, message.split(' ')))
        response = '0'
        if m in allowed:
            response = '1'
        await websocket.send(response)

start_server = websockets.serve(echo, 'IP_АДРЕС', 42690)

asyncio.get_event_loop().run_until_complete(start_server)
print('Сервер запущен на ws://IP_АДРЕС:42690')
asyncio.get_event_loop().run_forever()
