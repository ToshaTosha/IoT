from fastapi import FastAPI
from measurements.router import router as measurements_router
import uvicorn

app = FastAPI()

app.include_router(measurements_router, prefix="/measurements")

uvicorn.run(app, host="localhost", port=8000)