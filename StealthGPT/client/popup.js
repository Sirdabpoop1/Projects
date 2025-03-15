const CLIENT_ID = "984370571203-22h95ahurkhp6vclmg72dc10hfmf0u7i.apps.googleusercontent.com";
const SCOPES = ["https://www.googleapis.com/auth/documents"];


document.addEventListener("DOMContentLoaded", () => {
   document.getElementById("submit_button").addEventListener("click", handleSubmit);
});

async function handleSubmit() {
   const user_input = document.getElementById('prompt').value;
   const docId = document.getElementById('docId').value;
   
   if (!docId){
      document.getElementById('error_message').textContent = "Please enter a document ID";
      return;
   }
   
   document.getElementById('error_message').textContent = ""

   try {
      const accessToken = await authenticateUser();
      await sendTokenToBackend(accessToken, user_input, docId);
   }
   catch (error) {
      console.error("Error during authentication or API call:", error);
   }


}

async function authenticateUser(){
   return new Promise((resolve, reject) => {
      const redirectUri = chrome.identity.getRedirectURL();
      console.log("Redirect URI:", redirectUri);
      const authUrl = `https://accounts.google.com/o/oauth2/auth?client_id=${CLIENT_ID}&response_type=token&redirect_uri=https://fphmiepbhckbljkcjkmjceahfehlmeng.chromiumapp.org/&scope=${SCOPES.join(" ")}&prompt=consent`;

      chrome.identity.launchWebAuthFlow({ url: authUrl, interactive: true }, redirectUrl => {
         if (chrome.runtime.lastError) {
            console.error("Auth Error:", chrome.runtime.lastError.message);
            reject(chrome.runtime.lastError.message);
            return;
         }

         if (!redirectUrl) {
            reject("No redirect URL received.");
            return;
         }


         const urlParams = new URLSearchParams(new URL(redirectUrl).hash.substring(1));
         const accessToken = urlParams.get("access_token");
         
         if (accessToken){
            console.log("Access Token Retrieved:", accessToken);
            resolve(accessToken);
         }
         else{
            console.error("Failed to retrieve access token.");
            reject("No access token found.");
         }
      });
   })
};

async function sendTokenToBackend(token) {
   try {
      const response = await fetch('http://localhost:3000/stealth-gpt', {
         method: 'POST',
         headers: {
            'Content-Type': 'application/json',
         },
         body: JSON.stringify({ data: user_input }),
      });

      const data = await response.json()

      if (!data.message){
         console.log("its a boohoo :((")
      }

      document.getElementById('got_prompt').textContent = "Begin typing!"

      let i = 0;

      const keyupListener = async (event) => {
         if (i < data.message.length){
            try {
               await fetch('http://localhost:3000/stealth-gpt/typing',{
                  method: 'POST',
                  headers: {
                     'Content-Type': 'application/json',
                  },
                  body: JSON.stringify({ answer: data.message, DOCUMENTID: docId, accessToken: token})
               })
            }
            catch (error) {
               console.error('Error typing: ', error);
            }
            i += 15;
         }
         else {
            document.removeEventListener('keyup', keyupListener)
         }
      };
      document.addEventListener('keyup', keyupListener);
   }
   catch (error) {
      console.error('Error posting data:', error);
   }
}