import React from 'react';
import {Link} from 'react-router-dom';
import { Menu,  Row, Col,Avatar, Layout, PageHeader } from 'antd';
import Background from "../Background/index";
import { UserOutlined, NotificationOutlined } from '@ant-design/icons';
const { SubMenu } = Menu;

/**
* 用户后台的侧边栏
* 选择项目可以切换页面
* todo: 导航栏的选中信息刷新后没法保存
*/
class LeftSider extends React.Component {
    // Todo：获取用户权限，根据用户权限显示/隐藏部分页面
    constructor(props){
        super(props);
        this.state = {
            UserName:"用户A",
            isAdmin:true,
            isLoggedIn: true,
		    province: 1, //管理员所属省份
		    AdministerId: '001', // 假想的, 如果不是Administer最好存为null
        }
    }

	render() {
		return(
        <Row>
            <Col span={4}>
            <Layout className="site-page-header-ghost-wrapper" >
				<PageHeader ghost={false}
                    extra={[
						<Avatar size={32} icon={<UserOutlined />} />
					]}
                    title={"Hello," + "管理员"}>
				</PageHeader>						
			</Layout>
            <div>
                {
                    this.state.isAdmin?(
                    <Menu mode="inline" defaultSelectedKeys={["UserInfo"]} defaultOpenKeys={["Public"]} style={{ height: '100%', borderRight: 0 }}>
                    <Menu.Item key="UserInfo" icon ={<UserOutlined />}> <Link to = '/background/UserInfo'> 用户信息 </Link></Menu.Item>
                    <SubMenu key="Public" icon={<NotificationOutlined />} title="信息发布">
                    <Menu.ItemGroup>
                    <Menu.Item key="News"> <Link to = '/background/News'> 疫情新闻发布 </Link></Menu.Item>
                    <Menu.Item key="Cases"> <Link to ={{
                        pathname: '/background/Cases',
						state: {
						    id: this.state.AdministerId,
							province: this.state.province
						}
                    }}> 病例监测信息发布 </Link> </Menu.Item>
                    <Menu.Item key="Transportation"> <Link to = '/background/transportation'> 高危列车/航班信息发布 </Link></Menu.Item>
                    <Menu.Item key="ResumeAction"> <Link to = '/background/resumeaction'> 复工举措发布 </Link></Menu.Item>
                    <Menu.Item key="PopFlow"> <Link to = '/background/populationflow'> 人口流动信息发布 </Link></Menu.Item>
                    <Menu.Item key="Supplies"> <Link to = '/background/supplies'> 物资发布 </Link></Menu.Item>
                    </Menu.ItemGroup>
                    </SubMenu>
                    </Menu>

                    ):(
                    <Menu mode="inline" defaultSelectedKeys={["UserInfo"]} defaultOpenKeys={["Public"]} style={{ height: '100%', borderRight: 0 }}>
                    <Menu.Item key="UserInfo" icon ={<UserOutlined />}> <Link to = '/background/UserInfo'> 用户信息 </Link></Menu.Item>
                    </Menu>

                    )
                }
            </div>
            </Col>
            <Col span = {20}>
                <Background />
            </Col>
        </Row>
        );
	}
}

export default LeftSider