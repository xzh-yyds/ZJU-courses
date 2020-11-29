import React from 'react';
import $ from 'jquery';
import Map from './map.jsx';
import LineGraph from './line.jsx';
import Gauge from './gauge.jsx';
import { Link } from 'react-router-dom';
import { Layout, Menu, PageHeader, Button, Row, Statistic } from 'antd';
import './situation.css'
const { Content, Footer, Sider } = Layout;

class Situation extends React.Component {
	state = {
		// TODO: 登陆状态实时获取
		isLoggedIn: true,
		isAdminister: true,
		province: 1,
		AdministerId: '001', // 假想的, 如果不是Administer最好存为null
		prov_name: {
			'BJ':'北京',
			'TJ':'天津',
			'HE':'河北',
			'SX':'山西',
			'IM':'内蒙古',
			'LN':'辽宁',
			'JL':'吉林',
			'HL':'黑龙江',
			'SH':'上海',
			'JS':'江苏',
			'ZJ':'浙江',
			'AH':'安徽',
			'FJ':'福建',
			'JX':'江西',
			'SD':'山东',
			'HA':'河南',
			'HB':'湖北',
			'HN':'湖南',
			'GD':'广东',
			'GX':'广西',
			'HI':'海南',
			'CQ':'重庆',
			'SC':'四川',
			'GZ':'贵州',
			'YN':'云南',
			'XZ':'西藏',
			'SN':'陕西',
			'GS':'甘肃',
			'QH':'青海',
			'NX':'宁夏',
			'XJ':'新疆',
			'TW':'台湾',
			'HK':'香港',
			'MO':'澳门',
		},
		
		// 以下为测试数据
		json: {
				"array": [{
					"prov_name": "BJ",
					"diagnosed": 10,
					"dead": 5,
					"cured": 2,
					"suspected": 4,
					"abroad_in": 5,
					"asasymptomatic": 6
				},
				{
					"prov_name": "SH",
					"diagnosed": 15,
					"dead": 3,
					"cured": 3,
					"suspected": 4,
					"abroad_in": 5,
					"asasymptomatic": 6
				}
			]
		},
		json2: {
			"2020-06-01":{
				"prov_name": "BJ",
				"diagnosed": 500,
				"dead": 1000,
				"cured": 3000,
				"suspected": 4,
				"abroad_in": 5,
				"asasymptomatic": 6
			},
			"2020-06-02":{
				"prov_name": "BJ",
				"diagnosed": 1000,
				"dead": 2000,
				"cured": 2000,
				"suspected": 4,
				"abroad_in": 5,
				"asasymptomatic": 6
			}	
		}

	}

	getLoginState = () => {
		let self = this;
		// TODO: 获取登陆信息
	}

	getStatistics = () => {
		let that = this;

		var statistic = new Array(7).fill(0)
		var array = this.state.json["array"];
		for(var i = 0; i < array.length; i++){
			statistic[0] += array[i].diagnosed;
			statistic[1] += array[i].dead;
			statistic[2] += array[i].cured;
			statistic[3] += array[i].suspected;
			statistic[4] += array[i].abroad_in;
			statistic[5] += array[i].asasymptomatic;
		}
		statistic[6] += (statistic[0] - statistic[1] - statistic[2]);
		
		// TODO: 必须按顺序
		var lists = array.map(item => {
			return {
				// TODO：这里我觉得要给数组添加一个实名
				name: this.state.prov_name[item.prov_name],
				value: item.diagnosed
			}
		})
		
		// 传值设定state
		var cureRatio = statistic[2] / statistic[0] * 100
		var deadRatio = statistic[1] / statistic[0] * 100
		that.setState({
			statistic: statistic,
			cureRatio: cureRatio,
			deadRatio: deadRatio,
			mapData: lists
		})

		var answer = this.state.json2
		var dates = [], diagnosedList = [], deadList = [], curedList = [];
			for( var date in answer) {
				console.log(answer)
				dates.push(date);
				diagnosedList.push(answer[date].diagnosed);
				deadList.push(answer[date].dead);
				curedList.push(answer[date].cured);
			}
			// 传值设定state
			that.setState({
				diagnosedList: diagnosedList,
				deadList: deadList,
				curedList: curedList,
				dates: dates
			})
		/*
		!! TEST
		*/

	}

	getRearEnd = () => {
		let that = this;

		$.ajaxSetup({data: {csrfmiddlewaretoken: '{{ csrf_token}}' }});
		// TODO: 确认一下下面的URL, 以及下面的调用方法，不确定是否正确
		let url_1 = "/situation?getmap=true"
		let url_2 = "/situation?bydate=ture&getmap=true"
		$.getJSON(url_1, function(json){
			// TODO: 下面这个是否需要？
			console.log(json)
			var array = json["array"];
			console.log(array[0].dead)
			console.log(array[0]['dead'])
			// 处理全国六种人数统计
			var statistic = new Array(7).fill(0)
			for(var i = 0; i < array.length; i++){
				statistic[0] += array[i].diagnosed;
				statistic[1] += array[i].dead;
				statistic[2] += array[i].cured;
				statistic[3] += array[i].suspected;
				statistic[4] += array[i].abroad_in;
				statistic[5] += array[i].asymptomatic;
			}
			statistic[6] += (statistic[0] - statistic[1] - statistic[2]);
			console.log(statistic)
			
			// 处理全国各地确诊数量生成字典
			// TODO: 必须按一定的顺序, 参考原来那个url, 在map.json内
			// https://interface.sina.cn/news/wap/fymap2020_data.d.json?_=1580892522427
			var lists = array.map(item => {
				return {
					// TODO：这里我觉得要给数组添加一个实名
					name: that.state.prov_name[item.prov_name],
					value: item.diagnosed - item.dead - item.cured
				}
			})
			console.log(lists);
			
			// 传值设定state
			var cureRatio = Math.round(statistic[2] / statistic[0] * 100)
			var deadRatio = Math.round(statistic[1] / statistic[0] * 100)
			that.setState({
				statistic: statistic,
				cureRatio: cureRatio,
				deadRatio: deadRatio,
				mapData: lists
			})
			console.log(that.state.mapData);
		});

		$.getJSON(url_2, function(json){
			console.log(json)
			var arr = json["array"];

			// 处理每日全国各地三类数量生成几个列表
			var dates = [], diag_list = [], dead_list = [], cured_list = [];
			for(var i = 0; i < arr.length; i++){
				dates.push(arr[i]['date']);
				diag_list.push(arr[i]['diagnosed']);
				dead_list.push(arr[i]['dead']);
				cured_list.push(arr[i]['cured']);
			}

			// 传值设定state
			that.setState({
				diagnosedList: diag_list,
				deadList: dead_list,
				curedList: cured_list,
				dates: dates
			})
		})
	}

	componentWillMount() {
		this.getLoginState();
		this.getStatistics();
		this.getRearEnd();
	}
	render() {
		const isAdminister = (this.state.isLoggedIn && this.state.isAdminister);
		return (
			<Layout>
				<Content style={{ padding: '0 50px' }}>
					<Layout className="site-layout-background" style={{ marginTop: '24px'}}>
						<Layout >
							<Layout className="site-page-header-ghost-wrapper" style={{paddingRight:"20px", paddingBottom:"10px"}}>
								<PageHeader
								ghost={false}
								title="全国疫情数据"
								extra={[
									<div>
										<Link to="/situation/situationMoreInfo">
											<Button style={{marginLeft: "10px"}} key="1" type="primary">各省份详细数据</Button>
										</Link>
									</div>
								]}>
									<Row>
										<Statistic title="累计确诊" value={this.state.statistic[0]} style={{margin: '0 40px 0 0'}}/>
										<Statistic title="现有确诊" value={this.state.statistic[6]} style={{margin: '0 40px'}}/>
										<Statistic title="现有疑似" value={this.state.statistic[3]} style={{margin: '0 40px'}}/>
										<Statistic title="治愈出院" value={this.state.statistic[2]} style={{margin: '0 40px'}}/>	
										<Statistic title="死亡" value={this.state.statistic[1]} style={{margin: '0 40px'}}/>
										<Statistic title="无症状感染" value={this.state.statistic[5]} style={{margin: '0 40px'}}/>						
										<Statistic title="境外输入" value={this.state.statistic[4]} style={{margin: '0 0 0 40px'}}/>
									</Row>
								</PageHeader>
							</Layout>	
							<Layout style={{paddingRight:"20px", paddingTop:"10px"}} >
								<Map data={this.state.mapData}/>
							</Layout>					
						</Layout>

						<Sider className="site-layout-background" width={400}>
							<Layout className="site-page-header-ghost-wrapper" >
								<PageHeader
								ghost={false}
								title="全国疫情趋势"
								>
								</PageHeader>							
							</Layout>	
							<Layout style={{ paddingBottom:"10px"}}>
								<LineGraph dates={this.state.dates} cure={this.state.curedList} dead={this.state.deadList} diagnosed={this.state.diagnosedList}/>
							</Layout>	
							<Layout style={{ paddingTop:"10px" }}>
								<Gauge cureRatio={this.state.cureRatio} deadRatio={this.state.deadRatio}/>
							</Layout>
						</Sider>
					</Layout>
				</Content>
				
				<Footer style={{ textAlign: 'center' }}> ©2020 Created by G7, from course - Foundation Of SE</Footer>
			</Layout>
		)
	}
}

export default Situation