from fastapi import FastAPI
import uvicorn
from database import engine, Base
from measurements.router import router

Base.metadata.create_all(bind=engine)
app = FastAPI()
app.include_router(router)

if __name__ == '__main__':
    uvicorn.run(app, host='0.0.0.0', port=8005)
