const express = require("express");
const { GoogleGenerativeAI } = require("@google/generative-ai");
const cors = require("cors");
const { google } = require("googleapis");
require("dotenv").config();

let currentChar = 0;
let i = 1;

const app = express();
const port = 3000;
const genAI = new GoogleGenerativeAI(process.env.GOOGLE_API_KEY);
const model = genAI.getGenerativeModel({ model: 'gemini-1.5-flash' });

const oauth2Client = new google.auth.OAuth2(
   "984370571203-22h95ahurkhp6vclmg72dc10hfmf0u7i.apps.googleusercontent.com",
   null,
   "chrome-identity"
);


app.use(cors());
app.use(express.json());

app.post("/stealth-gpt", async (req, res) => {
   const { data  } = req.body;
   const result = await promptProcessing(data);
   res.json({message: result});
});

app.post("/stealth-gpt/typing", async (req, res) => {
   const { DOCUMENTID, answer, accessToken } = req.body;

   if (!accessToken){
      return res.status(401).json({ error: "Missing access token" });
   }

   oauth2Client.setCredentials({ token: accessToken });

   try{
      
      const docs = google.docs({ version: "v1", auth: oauth2Client });

      const requests = [
         {
            insertText: {
               location: {index: i},
               text: answer.slice(currentChar, currentChar += 15),
            },
         },
   ];
   await docs.documents.batchUpdate({
      documentId: DOCUMENTID,
      requestBody: {requests},
   });
   
   console.log("Printed!");
   i += 15;
   res.json({ message: "Typing completed successfully!" });
   } catch (error){
      console.error("Error printing to Google Docs: ", error);
      res.status(500).json({ error: "Failed to update Google Docs" });
   }
});


async function promptProcessing(data) {
   const answer_obj = await model.generateContent(data);
   const result = answer_obj.response.text()
   return result
}

app.listen(port, () => {
   console.log(`Stealth GPT listening on port ${port}`);
});