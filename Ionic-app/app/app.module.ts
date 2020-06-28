import { NgModule, ErrorHandler } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { IonicApp, IonicModule, IonicErrorHandler } from 'ionic-angular';
import { MyApp } from './app.component';

import { AboutPage } from '../pages/about/about';
import { monitoringPage } from '../pages/monitoring/monitoring';
import { ControlPage } from '../pages/control/control';
import { TabsPage } from '../pages/tabs/tabs';
import { AngularFireModule } from '@angular/fire';
import { AngularFirestoreModule } from '@angular/fire/firestore';
import { BackgroundGeolocation } from "@ionic-native/background-geolocation";
import { NativeAudio } from '@ionic-native/native-audio/ngx';





export const environment ={
  production: false, 
  firebase :{
    apiKey: "AIzaSyB_QJtqGvoAY0J-8W6EC9igcbaSjfl1Fbw",
    authDomain: "blindspotaduezz.firebaseapp.com",
    databaseURL: "https://blindspotaduezz.firebaseio.com",
    projectId: "blindspotaduezz",
    storageBucket: "blindspotaduezz.appspot.com",
    messagingSenderId: "756967053519",
    appId: "1:756967053519:web:6bb42a6df63d91e4867fba"
  }
};


@NgModule({
  declarations: [
    MyApp,
    AboutPage,
    monitoringPage,
    ControlPage,
    TabsPage
  ],
  imports: [
    BrowserModule,
    IonicModule.forRoot(MyApp),
    AngularFireModule.initializeApp(environment.firebase),
    AngularFirestoreModule,
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    MyApp,
    AboutPage,
    monitoringPage,
    ControlPage,
    TabsPage
  ],
  providers: [
    BackgroundGeolocation, 
    NativeAudio ,
    {provide: ErrorHandler, useClass: IonicErrorHandler}
  ]
})
export class AppModule {}
