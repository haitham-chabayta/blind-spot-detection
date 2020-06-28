
import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { AngularFirestore, AngularFirestoreCollection } from '@angular/fire/firestore';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';
import 'firebase/firestore';
import {BackgroundGeolocation, BackgroundGeolocationConfig, BackgroundGeolocationResponse } from '@ionic-native/background-geolocation';





export interface monitor {
  leftSense: String; 
  distance: String; 
  speed:String, 
};

@Component({
  selector: 'page-monitoring',
  templateUrl: 'monitoring.html'
})

export class monitoringPage {
  private monitoringCollection: AngularFirestoreCollection<monitor>;
  monitoringReadings: Observable<monitor[]>;

  speedReads:String;
  leftSensorReads:String;
  rightSensorReads:String;

  public lat;
  public lng;
  public speed;
  public watch: any;
  public x;


  constructor(public navCtrl: NavController , firestore: AngularFirestore,public bckGeo : BackgroundGeolocation){
    this.monitoringCollection = firestore.collection<monitor>('monitoring');

    this.monitoringReadings = this.monitoringCollection.valueChanges();
    this.monitoringReadings.subscribe((data)=>{
      
        this.speedReads = "0";
        this.leftSensorReads = data[1].distance;
        this.rightSensorReads = data[2].distance;

       

    });


    const config: BackgroundGeolocationConfig = {
            desiredAccuracy: 10,
            stationaryRadius: 20,
            distanceFilter: 30,
            debug: true, //  enable this hear sounds for background-geolocation life-cycle.
            stopOnTerminate: false, // enable this to clear background location settings when the app terminates
    };

   this.bckGeo.configure(config)
   .subscribe((location: BackgroundGeolocationResponse) => {

      // ERROR comes here ==> *subscribe* does not exist on type Promise<any> ???  
        var realSpeed = (3600/1000)*(location.speed);
        this.monitoringCollection.doc("basic").update({speed:realSpeed} ) ;

      });

      this.bckGeo.start();

    

   
  }


  





}



