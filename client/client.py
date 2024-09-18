import asyncio
import websockets

async def websocket_client():
    uri = "ws://localhost:8080"  
    async with websockets.connect(uri) as websocket:
        message = "Hola, servidor WebSocket"
        await websocket.send(message)
        print(f"Mensaje enviado: {message}")

        response = await websocket.recv()
        print(f"Respuesta recibida: {response}")

asyncio.get_event_loop().run_until_complete(websocket_client())
