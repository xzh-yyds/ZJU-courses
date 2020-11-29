import React from 'react';
import { Link, Redirect, Router, Route } from 'react-router-dom';
import { Layout, Form, Button, Input, Menu, Checkbox, Breadcrumb} from 'antd';
import PubCases from "./PubCases.jsx";

const { Header, Content, Footer } = Layout;
const layout = {
    labelCol: {
      span: 8,
    },
    wrapperCol: {
      span: 16,
    },
  };
const tailLayout = {
    wrapperCol: {
      offset: 8,
      span: 16,
    },
};

class SituationLogin extends React.Component {	

    constructor(props) {
        super(props);
        this.state = {
            loginFlag: false,
            table:[
                ['北京市病例监测管理员', "666"],
                ['上海市病例监测管理员', "666"],
                ['浙江省病例监测管理员', "666"]
            ],
            nametoID:{
                '北京市病例监测管理员':0,
                '天津市病例监测管理员':1,
                '河北省病例监测管理员':2,
                '山西省病例监测管理员':3,
                '内蒙古病例监测管理员':4,
                '辽宁省病例监测管理员':5,
                '吉林省病例监测管理员':6,
                '黑龙江省病例监测管理员':7,
                '上海市病例监测管理员':8,
                '江苏省病例监测管理员':9,
                '浙江省病例监测管理员':10,
                '安徽省病例监测管理员':11,
                '福建省病例监测管理员':12,
                '江西省病例监测管理员':13,
                '山东省病例监测管理员':14,
                '河南省病例监测管理员':15,
                '湖北省病例监测管理员':16,
                '湖南省病例监测管理员':17,
                '广东省病例监测管理员':18,
                '广西病例监测管理员':19,
                '海南省病例监测管理员':20,
                '重庆市病例监测管理员':21,
                '四川省病例监测管理员':22,
                '贵州省病例监测管理员':23,
                '云南省病例监测管理员':24,
                '西藏病例监测管理员':25,
                '陕西省病例监测管理员':26,
                '甘肃省病例监测管理员':27,
                '青海省病例监测管理员':28,
                '宁夏病例监测管理员':29,
                '新疆病例监测管理员':30,
                '台湾省病例监测管理员':31,
                '香港病例监测管理员':32,
                '澳门病例监测管理员':33,
            },
        }
    } 

    onFinish = values => {
        console.log('Success:', values);
        var pswd = values.password;
        var username = values.username;
        
        var k;
        console.log(this.state.table)
        for ( k = 0; k < this.state.table.length; k++) {
            if(this.state.table[k][0] == username && this.state.table[k][1] == pswd)
                break;
        }
        if( k == this.state.table.length){
            console.log('fail');
            window.alert("账号或密码错误");
        }
        else {
            console.log('success');
            this.setState({
                loginFlag: true
            })
            this.props.history.push('/background/Cases', {adname: username})
        }
    };
    
	render() {
		return (
			<Layout>
                <Content style={{ padding: '50px 50px 350px 50px' }}>
                    <Breadcrumb style={{ margin: '16px' }}>
                        <Breadcrumb.Item>Login</Breadcrumb.Item>
                        <Breadcrumb.Item>病例监测子系统自制登录</Breadcrumb.Item>
                    </Breadcrumb>
                    <Layout style={{padding:'0 650px'}}> 
                        <div style={{ width:"300px"}}>
                        <Form
                            {...layout}
                            name="basic"
                            initialValues={{
                                remember: true,
                            }}
                            onFinish={this.onFinish}
                            >
                            <Form.Item
                                label="管理员账号"
                                name="username"
                                rules={[
                                {
                                    required: true,
                                    message: 'Please input your username!',
                                },
                                ]}
                            >
                                <Input />
                            </Form.Item>

                            <Form.Item
                                label="密码"
                                name="password"
                                rules={[
                                {
                                    required: true,
                                    message: 'Please input your password!',
                                },
                                ]}
                            >
                                <Input.Password />
                            </Form.Item>

                            <Form.Item {...tailLayout} name="remember" valuePropName="checked">
                                <Checkbox>Remember me</Checkbox>
                            </Form.Item>

                            <Form.Item {...tailLayout}>
                                <Button type="primary" htmlType="submit">
                                Submit
                                </Button>
                            </Form.Item>
                        </Form>
                        </div>
                    </Layout>
                </Content>
				<Footer style={{ textAlign: 'center' }}> ©2020 Created by G7, from course - Foundation Of SE</Footer>
			</Layout>
		)
	}
}

export default SituationLogin