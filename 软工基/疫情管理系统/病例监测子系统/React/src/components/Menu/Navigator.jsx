import React from 'react';
import {Link} from 'react-router-dom';
import { Menu } from 'antd';
// 导入icon
import { LineChartOutlined, AppstoreOutlined, NotificationOutlined, CarOutlined, SolutionOutlined} from '@ant-design/icons';
const { SubMenu } = Menu;

/**
* 导航栏
* 选择项目可以切换页面
* todo: 导航栏的选中信息刷新后没法保存
*/
class Navi extends React.Component {
  state = {
    current: "graph",
  };

  handleClick = e => {
    console.log('click ', e);
    this.setState({
      current: e.key,
    });
  };

  render() {
    return (
      <Menu onClick={this.handleClick} selectedKeys={[this.state.current]} mode="horizontal">
        <Menu.Item key="graph" icon={<LineChartOutlined />}> <Link to = '/situation'> 国内疫情 </Link></Menu.Item>

        <Menu.Item key="news" icon={<AppstoreOutlined />}> <Link to = '/news'> 疫情新闻 </Link> </Menu.Item>

        <SubMenu icon={<CarOutlined />} title="同乘交通自查">
          <Menu.ItemGroup>
            <Menu.Item key="train"> <Link to = '/transportation/carcheck'> 列车自查 </Link> </Menu.Item>
            <Menu.Item key="flight"> <Link to = '/transportation/flightcheck'> 航班自查 </Link> </Menu.Item>
          </Menu.ItemGroup>
        </SubMenu>

        <SubMenu icon={<NotificationOutlined />} title="复工情况">
          <Menu.ItemGroup>
            <Menu.Item key="action"> <Link to = '/resumeaction'> 各省复工举措 </Link> </Menu.Item>
            <Menu.Item key="flow"> <Link to = '/populationflow'> 全国人口流动图 </Link> </Menu.Item>
          </Menu.ItemGroup>
        </SubMenu>

        <Menu.Item key="supplies" icon={<SolutionOutlined />}> <Link to = '/supplies'> 物资申领 </Link> </Menu.Item>
      </Menu>
    );
  }
}

export default Navi