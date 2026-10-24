import json
import os
from pathlib import Path

HISTORY_FILE = Path.home() / ".daily_ai_agent_history.json"

def load_history():
    try:
        if HISTORY_FILE.exists():
            with open(HISTORY_FILE, "r", encoding="utf-8") as f:
                return json.load(f)
    except:
        pass
    return []

def save_history(history):
    try:
        with open(HISTORY_FILE, "w", encoding="utf-8") as f:
            json.dump(history[-20:], f, ensure_ascii=False, indent=2)
    except:
        pass

def read_file(path):
    p = Path(path)
    if not p.exists():
        raise FileNotFoundError(f"File not found: {path}")
    ext = p.suffix.lower()
    text = ""
    if ext in [".txt", ".md", ".json", ".csv", ".log", ".py"]:
        with open(p, "r", encoding="utf-8", errors="ignore") as f:
            text = f.read()
    elif ext == ".pdf":
        try:
            from pypdf import PdfReader
            reader = PdfReader(p)
            for page in reader.pages:
                text += page.extract_text() + "\n"
        except Exception as e:
            raise RuntimeError(f"PDF read failed: {e}")
    elif ext in [".docx"]:
        try:
            from docx import Document
            doc = Document(p)
            for para in doc.paragraphs:
                text += para.text + "\n"
        except Exception as e:
            raise RuntimeError(f"DOCX read failed: {e}")
    else:
        with open(p, "r", encoding="utf-8", errors="ignore") as f:
            text = f.read()
    return text.strip()
