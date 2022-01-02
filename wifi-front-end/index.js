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
  console.log(switches.checked);
  switch (switches.id) {
    case "light1":
      switches.checked
        ? realtime.ref("switch").update({ light1: "1" })
        : realtime.ref("switch").update({ light1: "0" });
      break;
    case "light2":
      switches.checked
        ? realtime.ref("switch").update({ light2: "1" })
        : realtime.ref("switch").update({ light2: "0" });
      break;
    case "light3":
      switches.checked
        ? realtime.ref("switch").update({ light3: "1" })
        : realtime.ref("switch").update({ light3: "0" });
      break;
    case "light4":
      switches.checked
        ? realtime.ref("switch").update({ light4: "1" })
        : realtime.ref("switch").update({ light4: "0" });
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
    parseInt(snap.val().light1)
      ? (light1.checked = true)
      : (light1.checked = false);
    parseInt(snap.val().light2)
      ? (light2.checked = true)
      : (light2.checked = false);
    parseInt(snap.val().light3)
      ? (light3.checked = true)
      : (light3.checked = false);
    parseInt(snap.val().light4)
      ? (light4.checked = true)
      : (light4.checked = false);
  });
});
