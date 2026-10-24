SUMMARIZE = """Summarize the following content clearly and concisely.
Focus on key points, decisions, and action items if any.
Use bullet points. Keep it short and practical.

Content:
{content}"""

DRAFT_EMAIL = """Draft a {tone} email with the following details:
To: {to}
Subject: {subject}
Context: {context}

Include a clear subject, greeting, body, and closing. Keep it natural."""

TRANSLATE = """Translate the following text to {lang}.
Keep tone and meaning intact. If idioms don't translate well, suggest a natural alternative.
Text: {text}"""

EXTRACT_ACTIONS = """Extract all action items from this text.
For each, include: Task, Owner (if mentioned), Due (if mentioned), Priority (High/Med/Low).
Return as a clean bullet list.

Text: {text}"""

REWRITE = """Rewrite the text to be {goal}.
Fix grammar and clarity. Keep original intent.
Text: {text}"""

EXPLAIN = """Explain {topic} at {level} level.
Use simple words, examples if helpful, avoid jargon unless explained.
Topic: {topic}"""

QUICK_ANSWER = """Answer concisely in practical form.
Question: {q}"""
