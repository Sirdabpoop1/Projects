import base64
import pickle
import os
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.application import MIMEApplication
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
import gspread
from google.oauth2.service_account import Credentials

gspread_scopes = ["https://www.googleapis.com/auth/spreadsheets"]
creds = Credentials.from_service_account_file("gspread_credentials.json", scopes=gspread_scopes)
client = gspread.authorize(creds)

sheet_id = "1MPxFQCkgprBk3mNUAO-ZWVZaIfobZ3Wd4wzrBSZAYEw"

sh = client.open_by_key(sheet_id)

worksheet = sh.worksheet("SGS")

SCOPES = ["https://www.googleapis.com/auth/gmail.send"]
to_emails = worksheet.col_values(3)
del to_emails[0]
names = worksheet.col_values(1)
del names[0]
assignments = worksheet.col_values(4)
del assignments[0]


subject = "SCYMUN Delegate Assignment"

def authenticate():
    creds = None
    if os.path.exists("token.pickle"):
        with open("token.pickle", "rb") as token:
            creds = pickle.load(token)
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file("credentials.json", SCOPES)
            creds = flow.run_local_server(port = 0)
        
        with open("token.pickle", "wb") as token:
            pickle.dump(creds, token)

    return build("gmail", "v1", credentials=creds)

def send_email(to_email, body, pdf_file_path):
    service = authenticate()
    
    message = MIMEMultipart()
    message["to"] = to_email
    message["subject"] = subject

    message.attach(MIMEText(body, "html"))
    try:
        with open(pdf_file_path, "rb") as pdf_file:
            pdf_attatchment = MIMEApplication(pdf_file.read(), _subtype = "pdf")
            pdf_attatchment.add_header("Content-Disposition", "attachment", filename = os.path.basename(pdf_file_path))
            message.attach(pdf_attatchment)
    except Exception as e:
        print(f"Error: {e}")
        return

    raw_message = base64.urlsafe_b64encode(message.as_bytes()).decode()

    try:
        service.users().messages().send(
            userId="me",
            body={"raw": raw_message}
        ).execute()
        print(f"Email sent to {to_email}!")
    except Exception as e:
        print(f"Error: {e}")

def sending():
    
    i = 0
    for emails in to_emails:
        body = f"""
        <html>
        <head>
            <style>
                p {{ font-family: 'Times New Roman', serif; color: #000000; font-size: 14px; }}
            </style>
        </head>
        <body>
            <p>
                Dear {names[i]}, <br><br>

                Thank you for registering to participate in SCYMUN 2025, which is taking place on <strong>Tuesday, March 11 from 4pm-7:45pm.</strong> <br> <br>
                
                Your assignment was determined following thorough considerations regarding your prior experience and achievements in Model UN. We believe the selected delegation will grant you the greatest opportunity for success and growth. That being said, we are pleased to notify you of your committee and delegation assignment for SCYMUN 2025. <br> <br>
                
                Your assignment is as follows. <br> <br>

                Committee and Delegation:<strong> {assignments[i]} </strong><br> <br>

                To prepare for the conference, you should begin researching your committee's topic as well as your country's policies and diplomatic stances towards the topic. Please take a look at your committee's background guide that has been attached below. We strongly encourage you to read through the background guide first, as they give a comprehensive overview of your topic and serve as excellent starting points for your research. <br> <br>

                Best regards, <br>

                Saints Conference

            </p>
        </body>
        </html>
        """
        if "WHO" in assignments[i]:
            pdf_file_path = "backgrounders/WHO Backgrounders.docx.pdf"
        elif "EU" in assignments[i]:
            pdf_file_path = "backgrounders/EU Backgrounder.docx.pdf"
        else:
            pdf_file_path = "backgrounders/HCC Backgrounder.docx.pdf"
        send_email(emails, body, pdf_file_path)
        i += 1

sending()