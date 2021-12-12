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
  var switches = document.getElementById(name);
  console.log(switches.id);
  switch (switches.id) {
    case "light1":
      realtime.ref("switch").update({ light1: switches.checked });
      break;
    case "light2":
      realtime.ref("switch").update({ light2: switches.checked });
      break;
    case "light3":
      realtime.ref("switch").update({ light3: switches.checked });
      break;
    case "light4":
      realtime.ref("switch").update({ light4: switches.checked });
      break;
  }
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
  var light1 = document.getElementById("light1");
  var light2 = document.getElementById("light2");
  var light3 = document.getElementById("light3");
  var light4 = document.getElementById("light4");
  realtime.ref("switch").on("value", (snap) => {
    light1.checked = snap.val().light1;
    light2.checked = snap.val().light2;
    light3.checked = snap.val().light3;
    light4.checked = snap.val().light4;
  });
});
