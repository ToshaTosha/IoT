from sqlalchemy.orm import Session
from fastapi import APIRouter, Depends
from database import get_db
from measurements.schemas import User
import measurements.services as services

router = APIRouter()

@router.post("/registration", tags=["registration"])
async def create_temperature(request: User, db: Session=Depends(get_db)):
    return services.user_registration(request, db)
