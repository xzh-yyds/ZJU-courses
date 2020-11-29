import React from 'react'
// 引入各组件
import UserInfo from "../../page/Users/UserInfo";
import PubNews from "../../page/news/PubNews";
import PubCases from "../../page/situation/PubCases";
import PubTrans from "../../page/transportation/PubTrans";
import PubAction from "../../page/resume/PubAction";
import PubFlow from "../../page/resume/PubFlow";
import PubSupplies from "../../page/supplies/PubSupplies";

//引入路由
import {Route, Switch} from 'react-router-dom'

/**
 * 用户后台主体部分
 * 设置各子系统路由，默认显示用户信息页
 */
class Background extends React.Component {
	render() {
		return (
			<div>
				<Switch>
                    {/**path应加上用户名/省份名等标识 */}
					<Route exact path='/background/UserInfo' component={UserInfo}/>
					<Route exact path='/background/News' component={PubNews}/>
					<Route exact path='/background/Cases' component={PubCases}/>
					<Route exact path='/background/transportation' component={PubTrans}/>
					<Route exact path='/background/resumeaction' component={PubAction}/>
                    <Route exact path='/background/populationflow' component={PubFlow}/>
					<Route exact path='/background/supplies' component={PubSupplies}/>
				</Switch>
			</div>
		)
	}
}

export default Background