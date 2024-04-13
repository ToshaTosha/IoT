from sqlalchemy.orm import Session
from fastapi import APIRouter, Depends
from database import get_db
from src.schemas import User
from src.schemas import User, Device, Color
import src.services as services

router = APIRouter()

@router.post("/user_registration")
async def create_user(request: User, db: Session = Depends(get_db)):
   return services.registration_handler(request, db, User)

@router.post("/device_registration")
async def create_device(request: Device, db: Session = Depends(get_db)):
   return services.registration_handler(request, db, Device)

@router.post("/color_registration")
async def create_color(request: Color, db: Session = Depends(get_db)):
   return services.registration_handler(request, db, Color)
