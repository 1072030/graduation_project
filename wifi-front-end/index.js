function update(name) {
  const config = {
    apiKey: "AIzaSyBSpYcL35JxpTzitkFrN4WJNW0oaiES1Z8",
    authDomain: "beacon-backend-a8bf3.firebaseapp.com",
    databaseURL:
      "https://beacon-backend-a8bf3-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "beacon-backend-a8bf3",
    storageBucket: "beacon-backend-a8bf3.appspot.com",
    messagingSenderId: "946463586855",
    appId: "1:946463586855:web:c811f50af9ed244ffcec02",
    measurementId: "${config.measurementId}",
  };
  firebase.initializeApp(config);
  const realtime = firebase.database();
  var i = document.getElementById(name);
  console.log(i.checked);
  realtime.ref("switch").set({ light: i.checked });
}

$(function () {
  const config = {
    apiKey: "AIzaSyBSpYcL35JxpTzitkFrN4WJNW0oaiES1Z8",
    authDomain: "beacon-backend-a8bf3.firebaseapp.com",
    databaseURL:
      "https://beacon-backend-a8bf3-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "beacon-backend-a8bf3",
    storageBucket: "beacon-backend-a8bf3.appspot.com",
    messagingSenderId: "946463586855",
    appId: "1:946463586855:web:c811f50af9ed244ffcec02",
    measurementId: "${config.measurementId}",
  };
  firebase.initializeApp(config);
  const realtime = firebase.database();
  var i = $("#flexSwitchCheckChecked");
  console.log(i);
  realtime.ref("switch").set({ light: true });
  realtime.ref("switch").on("value", (snap) => {
    console.log(snap.val().light);
  });
});
