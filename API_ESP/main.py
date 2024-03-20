from fastapi import FastAPI
import uvicorn
from database import SessionLocal, engine, Base
from measurements.router import router

Base.metadata.create_all(bind=engine)
app = FastAPI()
app.include_router(router)

if __name__ == '__main__':
    uvicorn.run(app, host='localhost', port=8005)
