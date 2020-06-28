import { Component } from '@angular/core';

import { AboutPage } from '../about/about';
import { monitoringPage } from '../monitoring/monitoring';
import { ControlPage } from '../control/control';

@Component({
  templateUrl: 'tabs.html'
})
export class TabsPage {

  tab1Root =  ControlPage;
  tab2Root = monitoringPage;
  tab3Root = AboutPage;

  constructor() {

  }
}
