import React, {Component} from 'react';

//路由
import {BrowserRouter} from 'react-router-dom';

//布局组件
import Menu from "./components/Menu/Menu";//导航
import ContentMain from "./components/ContentMain/index";//主题

class App extends Component {
	render() {
		return (
			<div className="App" >
				<BrowserRouter>
				    <Menu />
					<ContentMain/>
				</BrowserRouter>
			</div>
		);
	}
}
export default App;
