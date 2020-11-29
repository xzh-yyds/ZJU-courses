import React from 'react'
// 导入各子系统组件

import SituationLogin from '../../page/situation/Login'
import Situation from '../../page/situation/show/index'
import News from '../../page/news/index'
import CarCheck from '../../page/transportation/carcheck'
import FlightCheck from '../../page/transportation/flightcheck'
import ResumeAction from '../../page/resume/resumeaction'
import PopulationFlow from '../../page/resume/flow'
import Supplies from '../../page/supplies/index'
import LeftSider from '../Menu/Sider'
import SituationMoreInfo from '../../page/situation/situationMoreInfo/index'
//引入路由
import {Route, Switch} from 'react-router-dom'

/**
 * 网页主体部分
 * 设置各子系统路由，默认将全国疫情地图作为首页
 */
class ContentMain extends React.Component {
	render() {
		return (
			<div>
				<Switch>
					<Route exact path='/situation/login' component={SituationLogin}/>
					<Route exact path='/situation' component={Situation}/>
					<Route exact path='/situation/situation' component={Situation}/>
					<Route exact path='/situation/situationMoreInfo' component={SituationMoreInfo}/>
					<Route exact path='/news' component={News}/>
					<Route exact path='/transportation/carcheck' component={CarCheck}/>
                    <Route exact path='/transportation/flightcheck' component={FlightCheck}/>
					<Route exact path='/resumeaction' component={ResumeAction}/>
                    <Route exact path='/populationflow' component={PopulationFlow}/>
					<Route exact path='/supplies' component={Supplies}/>
					<Route path='/background' component={LeftSider}/>
					<Route render={() => <h1 className={''}>找不到此页面</h1>} />
				</Switch>
			</div>
		)
	}
}

export default ContentMain