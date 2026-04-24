from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse
from fastapi.staticfiles import StaticFiles
import time

app = FastAPI()

data_store = []



@app.post("/data")
async def receive_data(req: Request):
    data = await req.json()

    if "timestamp" not in data:
        data["timestamp"] = int(time.time())

    data_store.append(data)

    return {"status": "ok"}


@app.get("/data")
async def get_data():
    return data_store[-200:]



app.mount("/", StaticFiles(directory="frontend", html=True), name="frontend")