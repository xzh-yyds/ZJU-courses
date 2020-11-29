import React from 'react';
import {Button} from 'antd';
import {Link} from 'react-router-dom';
import Navi from './Navigator';
import Logo from '../../image/logo.jpg';
import './Menu.css';

/**
 * logo + 导航栏
 * 登录/注册的按钮只是个样子
 */
class Menu extends React.Component{
    // 控制后台菜单的显示
    constructor(props){
        super(props);
        this.state = {
            isLoggined:true
        }
    }

    render(){
        return(
            <div class = "header">
                <img class = "logo" src = {Logo} alt="校徽" />
                <div class ="title"> 疫情管控系统 </div>
                <div style = {{alignSelf:'flex-end'}}> <Navi /> </div>
                <div style = {{marginLeft: 'auto'}}>
                    <div>{
                        this.state.isLoggined?(
                            <Button type="primary" size="large"><Link to = '/situation/login'> 登录/注册  </Link></Button>
                        ):(
                            <Button type="primary" size="large"> 登录/注册 </Button>
                        )
                        }
                    </div>
                </div>
            </div>
        );
    }
}

export default Menu