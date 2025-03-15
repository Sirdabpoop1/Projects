import base64
import pickle
import os
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
to_emails = worksheet.col_values(6)
del to_emails[0]
names = worksheet.col_values(5)
del names[0]


subject = "An Update To Your SCYMUN Staff Application"

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

def send_email(to_email, body):
    service = authenticate()
    
    message = MIMEText(body, "html")
    message["to"] = to_email
    message["subject"] = subject
    
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

                We hope this email finds you well. On behalf of Saint George’s Leadership, we would like to thank you for your interest in joining the SCYMUN 2025 staff team.<br> <br>
                
                This year, we have received a substantial amount of strong applications from St. George’s. After a thorough review of your application, I regret to inform you that we are unable to offer you a staff position at this time. We appreciate your dedication to Model UN and strongly encourage you to continue applying for staff positions. We truly hope that this setback does not discourage you from pursuing MUN in the future.<br> <br>
                
                If you indicated that you would like to delegate at SCYMUN on the staff application form, you will be contacted about your position shortly. If you didn't and would still like to participate in SCYMUN as a delegate, please reply to this email as soon as possible. <br> <br>

                Should you have any questions regarding this statement, do not hesitate to contact us. </strong><br> <br>

                Sincerely, <br>
                
                Saints Conference

            </p>
        </body>
        </html>
        """
        send_email(emails, body)
        i += 1

sending()