import os
from dotenv import load_dotenv

load_dotenv()

class Config:
    PROVIDER = os.getenv("PROVIDER", "groq").lower()
    MODEL = os.getenv("MODEL", "llama-3.1-8b-instant")
    API_KEY = os.getenv("API_KEY", "")
    BASE_URL = os.getenv("BASE_URL", "")
    TEMPERATURE = float(os.getenv("TEMPERATURE", "0.2"))
    MAX_HISTORY = int(os.getenv("MAX_HISTORY", "10"))
    SYSTEM_PROMPT = os.getenv("SYSTEM_PROMPT", "You are a helpful, concise daily assistant. Give practical answers, use bullet lists when helpful, and avoid fluff.")

config = Config()
