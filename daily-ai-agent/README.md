# Daily AI Agent

A lightweight CLI agent that helps with everyday tasks: summarize text/files, draft emails/messages, answer questions, translate, extract action items, and give quick advice. Runs locally with your OpenAI/Anthropic/Groq/OpenRouter key or offline via Ollama.

## Features

- **Chat**: Interactive Q&A with memory of recent conversation
- **Summarize**: Summarize files (txt, md, pdf, json, csv) or pasted text
- **Draft**: Generate emails, messages, replies, or LinkedIn posts
- **Translate**: Translate between languages with tone/usage notes
- **Action Items**: Extract to-do's, deadlines, owners from notes/meetings
- **Rewrite**: Improve clarity, tone, grammar, or shorten/expand
- **Explain**: Explain code, concepts, or jargon at any level
- **Quick Ask**: One-shot questions without entering chat
- **CLI-First**: Fast, minimal, works in terminal/WSL/PowerShell

## Setup

### 1) Install dependencies

```bash
cd daily-ai-agent
python -m venv .venv
# Windows
.venv\Scripts\activate
# Linux/WSL/macOS
source .venv/bin/activate
pip install -r requirements.txt
```

### 2) Configure API key

Copy `.env.example` to `.env` and add your key:

```bash
cp .env.example .env
```

```env
PROVIDER=groq
MODEL=llama-3.1-8b-instant
API_KEY=your_key_here
BASE_URL=
TEMPERATURE=0.2
MAX_HISTORY=10
```

Supported providers: `openai`, `anthropic`, `groq`, `openrouter`, `ollama` (local). For Ollama set `PROVIDER=ollama`, `MODEL=llama-3.1` or `gemma2`, `BASE_URL=http://localhost:11434/v1/chat/completions` or use the native client via the script.

### 3) Run

```bash
python agent.py
# or
./agent.py --help
```

## Usage

```text
/ask What is Docker in simple terms
/summarize meeting_notes.txt
/draft email to client apologizing for delay
/translate "Hello world" to Hindi
/extract todo meeting_transcript.txt
/rewrite "u need to fix this asap" to polite professional
/explain "async/await" for a beginner
/clear  # clear history
/help
/exit
```

Or quick one-shot:

```bash
python agent.py ask "Give me 3 ideas for lunch"
python agent.py summarize README.md
```

## Files

```
daily-ai-agent/
├── agent.py        # CLI entrypoint
├── config.py       # env/config loader
├── prompts.py      # reusable prompts
├── utils.py        # helpers (files, history)
├── requirements.txt
├── .env.example
└── README.md
```

## Tips

- Use `/summarize` on long emails/threads to save time.
- Use `/extract` after meetings to get actionable items instantly.
- Set `PROVIDER=ollama` for offline/private use.
- Keep `MAX_HISTORY` small to save tokens/costs.

## License

MIT
