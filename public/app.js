// Firebase Configuration
var firebaseConfig = {
    authDomain: "smarttraffic-11.firebaseapp.com", // Replace with your project ID
    databaseURL: "https://smarttraffic-11.firebaseio.com", // Replace with your database URL
    projectId: "smarttraffic-11", // Replace with your project ID
    storageBucket: "smarttraffic-11.appspot.com", // Replace with your project ID
    messagingSenderId: "BBtYhy38EdgmxcdlNXhNu_cid_x1jOXllzfRod98WYDdzbPUrcqRE3YyG16HUblx57WWNGkT7LvFa9dfApCiy98", // Replace with your messaging sender ID
    appId: "1:205250504694:web:8b729d92eca493b17709d7" // Replace with your app ID
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);

// Reference Firebase Realtime Database
var trafficRef = firebase.database().ref('traffic_data/current_status');

// Listen for real-time updates
trafficRef.on('value', (snapshot) => {
    const trafficData = snapshot.val();
    document.getElementById('traffic-data').innerHTML = trafficData;
});
