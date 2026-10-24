#!/usr/bin/env python3
import sys
import json
from pathlib import Path
from rich.console import Console
from rich.panel import Panel
from rich.prompt import Prompt
from rich.markdown import Markdown
import typer
from openai import OpenAI
from anthropic import Anthropic
from config import config
from prompts import *
from utils import load_history, save_history, read_file

app = typer.Typer(add_completion=False, help="Daily AI Agent CLI")
console = Console()
history = load_history()

client = None
if config.PROVIDER in ["openai", "groq", "openrouter", "ollama"]:
    base_url = config.BASE_URL or None
    if config.PROVIDER == "groq":
        base_url = base_url or "https://api.groq.com/openai/v1"
    elif config.PROVIDER == "openrouter":
        base_url = base_url or "https://openrouter.ai/api/v1"
    elif config.PROVIDER == "ollama":
        base_url = base_url or "http://localhost:11434/v1"
    client = OpenAI(api_key=config.API_KEY or "ollama", base_url=base_url)
elif config.PROVIDER == "anthropic":
    client = Anthropic(api_key=config.API_KEY)

def call_llm(messages):
    try:
        if config.PROVIDER == "anthropic":
            system = None
            msgs = []
            for m in messages:
                if m["role"] == "system":
                    system = m["content"]
                else:
                    msgs.append(m)
            resp = client.messages.create(
                model=config.MODEL,
                max_tokens=1024,
                temperature=config.TEMPERATURE,
                system=system,
                messages=msgs,
            )
            return resp.content[0].text
        else:
            resp = client.chat.completions.create(
                model=config.MODEL,
                messages=messages,
                temperature=config.TEMPERATURE,
                max_tokens=1024,
            )
            return resp.choices[0].message.content
    except Exception as e:
        console.print(f"[red]Error:[/red] {e}")
        return None

def get_messages(user_msg):
    msgs = [{"role": "system", "content": config.SYSTEM_PROMPT}]
    for h in history[-config.MAX_HISTORY:]:
        msgs.append(h)
    msgs.append({"role": "user", "content": user_msg})
    return msgs

@app.command()
def ask(q: str):
    """Quick one-shot question"""
    msgs = get_messages(q)
    ans = call_llm(msgs)
    if ans:
        console.print(Markdown(ans))
        history.append({"role": "user", "content": q})
        history.append({"role": "assistant", "content": ans})
        save_history(history)

@app.command()
def summarize(file_or_text: str):
    """Summarize a file or text"""
    try:
        if Path(file_or_text).exists():
            content = read_file(file_or_text)
        else:
            content = file_or_text
        prompt = SUMMARIZE.format(content=content)
        msgs = get_messages(prompt)
        ans = call_llm(msgs)
        if ans:
            console.print(Panel(Markdown(ans), title="Summary"))
            history.append({"role": "user", "content": f"/summarize {file_or_text}"})
            history.append({"role": "assistant", "content": ans})
            save_history(history)
    except Exception as e:
        console.print(f"[red]{e}[/red]")

@app.command()
def draft(to: str = "someone", subject: str = "Message", context: str = "", tone: str = "polite and professional"):
    """Draft an email/message"""
    prompt = DRAFT_EMAIL.format(to=to, subject=subject, context=context, tone=tone)
    msgs = get_messages(prompt)
    ans = call_llm(msgs)
    if ans:
        console.print(Panel(Markdown(ans), title="Draft"))
        history.append({"role": "user", "content": f"/draft {to} {subject}"})
        history.append({"role": "assistant", "content": ans})
        save_history(history)

@app.command()
def translate(text: str, to: str = "English"):
    """Translate text"""
    prompt = TRANSLATE.format(text=text, lang=to)
    msgs = get_messages(prompt)
    ans = call_llm(msgs)
    if ans:
        console.print(Panel(ans, title="Translation"))
        history.append({"role": "user", "content": f"/translate to {to}"})
        history.append({"role": "assistant", "content": ans})
        save_history(history)

@app.command()
def extract(file_or_text: str):
    """Extract action items"""
    try:
        if Path(file_or_text).exists():
            content = read_file(file_or_text)
        else:
            content = file_or_text
        prompt = EXTRACT_ACTIONS.format(text=content)
        msgs = get_messages(prompt)
        ans = call_llm(msgs)
        if ans:
            console.print(Panel(Markdown(ans), title="Action Items"))
            history.append({"role": "user", "content": f"/extract {file_or_text}"})
            history.append({"role": "assistant", "content": ans})
            save_history(history)
    except Exception as e:
        console.print(f"[red]{e}[/red]")

@app.command()
def rewrite(text: str, goal: str = "clear and professional"):
    """Rewrite text"""
    prompt = REWRITE.format(text=text, goal=goal)
    msgs = get_messages(prompt)
    ans = call_llm(msgs)
    if ans:
        console.print(Panel(ans, title="Rewritten"))
        history.append({"role": "user", "content": f"/rewrite {goal}"})
        history.append({"role": "assistant", "content": ans})
        save_history(history)

@app.command()
def explain(topic: str, level: str = "beginner"):
    """Explain a topic"""
    prompt = EXPLAIN.format(topic=topic, level=level)
    msgs = get_messages(prompt)
    ans = call_llm(msgs)
    if ans:
        console.print(Panel(Markdown(ans), title="Explanation"))
        history.append({"role": "user", "content": f"/explain {topic}"})
        history.append({"role": "assistant", "content": ans})
        save_history(history)

@app.command()
def chat():
    """Interactive chat mode"""
    console.print(Panel("Daily AI Agent - Chat Mode\nType '/help' or '/exit'", title="Interactive"))
    while True:
        try:
            user = Prompt.ask("[bold cyan]You[/bold cyan]")
            if not user.strip():
                continue
            if user.strip() in ["/exit", "exit", "quit"]:
                break
            if user.strip() == "/clear":
                history.clear()
                save_history(history)
                console.print("[yellow]History cleared[/yellow]")
                continue
            if user.strip() == "/help":
                console.print(Markdown("**Commands:** /ask, /summarize, /draft, /translate, /extract, /rewrite, /explain, /clear, /exit"))
                continue
            msgs = get_messages(user)
            ans = call_llm(msgs)
            if ans:
                console.print(Panel(Markdown(ans), title="Agent"))
                history.append({"role": "user", "content": user})
                history.append({"role": "assistant", "content": ans})
                save_history(history)
        except KeyboardInterrupt:
            break
        except Exception as e:
            console.print(f"[red]{e}[/red]")

if __name__ == "__main__":
    if len(sys.argv) == 1:
        chat()
    else:
        app()
