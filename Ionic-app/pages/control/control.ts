import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { AngularFirestore, AngularFirestoreCollection } from '@angular/fire/firestore'
import 'firebase/firestore';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';
export interface Control { id:string; type: string; value: number; name:string }

@Component({
  selector: 'page-home',
  templateUrl: 'control.html'
})



export class ControlPage {

  muteState:boolean
  turnOffState:boolean
  cntrlSpeedState:boolean

  private controlCollection: AngularFirestoreCollection<Control>;
  
  constructor(public navCtrl: NavController,firestore: AngularFirestore) {
    this.controlCollection = firestore.collection<Control>('controls');
    this.muteState = false;
    this.turnOffState = false;
    this.cntrlSpeedState = false;
      
  }

   muteApp(){
     var muteStateNo:Number
     this.muteState = !this.muteState;
     muteStateNo =(this.muteState)? 1:0;
     this.controlCollection.doc("controlling").update({mute: muteStateNo});
     console.log("muteStateNo "+muteStateNo);
   }


   turnOffHost(){
     var turnOffStateNo:Number
     this.turnOffState = !this.turnOffState;
     turnOffStateNo =(this.turnOffState)? 1:0;
     this.controlCollection.doc("controlling").update({turnOff: turnOffStateNo});
     console.log("turnOff "+turnOffStateNo);
   }

    speedControl(){
     var cntrlSpeedStateNo:Number
     this.cntrlSpeedState = !this.cntrlSpeedState;
     cntrlSpeedStateNo =(this.cntrlSpeedState)? 1:0;
     this.controlCollection.doc("controlling").update({cntrlSpeed: cntrlSpeedStateNo});
     console.log("speedControl "+cntrlSpeedStateNo);
    }

   getSpeed(){
     
   }


}
