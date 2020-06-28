import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { AngularFirestore, AngularFirestoreCollection } from '@angular/fire/firestore';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';
import 'firebase/firestore';
import { AlertController , Platform } from 'ionic-angular';
import { NativeAudio } from '@ionic-native/native-audio/ngx';


export interface monitoringData {distance:String , speed:String };
export interface controllingData {mute:Number , cntrlSpeed:Number };

@Component({
  selector: 'page-about',
  templateUrl: 'about.html'
})
export class AboutPage {
  private monitoringCollection: AngularFirestoreCollection<monitoringData>;
  monitoringReadings: Observable<monitoringData[]>;


  private controllingCollection: AngularFirestoreCollection<controllingData>;
  controllingReadings: Observable<controllingData[]>;

 
  leftside:boolean;
  rightside:boolean;
  muteState:Number;
  controlledSpeed:Number;
  lft:String;
  rght:String;
  speed:String;

  

  constructor(public navCtrl: NavController , firestore: AngularFirestore , private nativeAudio: NativeAudio
  ) {
    this.leftside = false;
    this.rightside = false;


    this.controllingCollection = firestore.collection< controllingData>('controls');
    this.controllingReadings = this.controllingCollection.valueChanges();

    this.controllingReadings.subscribe((data)=>{
      this.muteState = data[0].mute;
      this.controlledSpeed = data[0].cntrlSpeed;
      
     
        
    });



    this.monitoringCollection = firestore.collection< monitoringData>('monitoring');
    this.monitoringReadings = this.monitoringCollection.valueChanges();

    this.monitoringReadings.subscribe((data)=>{
      this.lft = data[1].distance;
      this.rght = data[2].distance;
      this.speed = data[0].speed;
      
      var nwLft = +this.lft;
      var nwRght = +this.rght;
      var nwSpeed = +this.speed;

      var muteBool:boolean = (this.muteState == 1)? true : false;
      var cntrlSpeedBool: boolean = (this.controlledSpeed == 1)? true : false;

      switch(cntrlSpeedBool){
        case true :
          if(nwLft<50 && nwSpeed>80 ){
            this.leftside = true;
            
            //if(!muteBool)
              //this.alarmSound()
            console.log("left");
          }else{
            this.leftside = false;
          }

          if(nwRght<50 && nwSpeed>80){  
            this.rightside = true;
            //if(!muteBool)
              //this.alarmSound();
            console.log("Right");
          }else{
            this.rightside = false;
          } 
         break ;
        case false:
          if(nwLft<50){
            this.leftside = true;
            //if(!muteBool)
              //this.alarmSound();
            console.log("left");
          }else{
            this.leftside = false;
          }

          if(nwRght<50){  
            this.rightside = true;
            //if(!muteBool)
              //this.alarmSound();
            console.log("Right");
          }else{
            this.rightside = false;
          }
         break;
      }
      



        
    });


    
   
  }

  alarmSound(){
    this.nativeAudio.preloadSimple('uniqueId1', 'http://codeskulptor-demos.commondatastorage.googleapis.com/pang/pop.mp3');
        this.nativeAudio.play('uniqueId1');
        this.nativeAudio.setVolumeForComplexAsset('uniqueId2', 1);
        this.nativeAudio.stop('uniqueId1');
  }


  

}
