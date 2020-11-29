import React from 'react';
import $ from 'jquery';
import { Select, Layout, Menu, PageHeader, Button, Row, Statistic } from 'antd';
import './situation.css'
import Statistics from './Statistics.jsx'
import LineThreeType from './lineThreeType.jsx'
import LineOneType from './line.jsx'
import Gauge from './gauge.jsx'

const { Option } = Select;
const { SubMenu } = Menu;
const { Header, Content, Footer, Sider } = Layout;

class SituationMoreInfo extends React.Component {
	state = {
		provinceId: 0,
		provinceData: {
			0:['北京','BF'],
            1:['天津','TJ'],
        	2:['河北','HE'],
        	3:['山西','SX'],
            4:['内蒙古','IM'],
            5:['辽宁','LN'],
            6:['吉林','JL'],
            7:['黑龙江','HL'],
            8:['上海','SH'],
            9:['江苏','JS'],
            10:['浙江','ZJ'],
            11:['安徽','AH'],
            12:['福建','FJ'],
            13:['江西','JX'],
            14:['山东','SD'],
            15:['河南','HA'],
            16:['湖北','HB'],
            17:['湖南','HN'],
            18:['广东','GD'],
            19:['广西','GX'],
            20:['海南','HI'],
            21:['重庆','CQ'],
            22:['四川','SC'],
            23:['贵州','GZ'],
            24:['云南','YN'],
            25:['西藏','XZ'],
            26:['陕西','SN'],
            27:['甘肃','GS'],
            28:['青海','QH'],
            29:['宁夏','NX'],
            30:['新疆','XJ'],
            31:['台湾','TW'],
            32:['香港','HK'],
            33:['澳门','MO'],
		},

		/* !! TEST */
		json: {
			"2020-06-01":{
				"prov_name": "BJ",
				"diagnosed": 400,
				"dead": 200,
				"cured": 100,
				"suspected": 50,
				"abroad_in": 50,
				"asasymptomatic": 25
			},
			"2020-06-02":{
				"prov_name": "BJ",
				"diagnosed": 500,
				"dead": 300,
				"cured": 100,
				"suspected": 60,
				"abroad_in": 60,
				"asasymptomatic": 50
			}	
		},
		json2: {
			"2020-06-01":{
				"prov_name": "SH",
				"diagnosed": 500,
				"dead": 1300,
				"cured": 3000,
				"suspected": 4,
				"abroad_in": 5,
				"asasymptomatic": 6
			},
			"2020-06-02":{
				"prov_name": "SH",
				"diagnosed": 1200,
				"dead": 2300,
				"cured": 2000,
				"suspected": 4,
				"abroad_in": 500,
				"asasymptomatic": 6
			}	
		}
		
	}
	constructor(props) {
		super(props)
	}
	componentWillMount() {
		// TODO: url check
		var url = "/situation/situationMoreInfo?bydate=true&province=" + "BJ"
		this.getProvinceList();
		this.getStatistic();
		this.getRearEnd(url);
	}
	shouldComponentUpdate(nextProps, nextState){
		return true;
	}

	getProvinceList(){
		var data = this.state.provinceData;
		var list = [];
		for (var key in data) {
			var province = data[key];
			var dic = {};
			dic["name"] = province[0];
			dic["short"] = province[1];
			dic["provinceId"] = key;
			list.push(dic);
		}
		this.state.provinceList = list
		console.log(this.state.provinceList)
	};
	handleChange = value => {
		this.setState({
			provinceId: value
		}, () => {
			var provinceShortName = this.state.provinceList[this.state.provinceId].short
			console.log("cur provinceName", provinceShortName)
			// TODO: 确认一下下面的URL，不确定是否正确, 这个是省份数据获取
			var url = "/situation/situationMoreInfo?bydate=true&province=" + provinceShortName
			// 分离
			this.getRearEnd(url)
		});
	}

	getRearEnd = (url) => {
		// TODO：以下部分类似于situation里面
		// GET JSON
		$.ajaxSetup({data: {csrfmiddlewaretoken: '{{ csrf_token}}' }});
		let that = this;

		// 以下获取每日省份数据并处理，参照测试数据json
		$.getJSON(url, function(json){
			console.log(json)
			var arr = json["array"];
			// 当前日期获取
			var curData = {}
			// for( var k in arr ) {
			// 	curData = k
			// }
			for(var i = 0; i < arr.length; i++){
				curData = arr[i]
			}
			// 处理省份六种人数统计
			var statistic = new Array(7).fill(0)
			statistic[0] += curData.diagnosed;
			statistic[1] += curData.dead;
			statistic[2] += curData.cured;
			statistic[3] += curData.suspected;
			statistic[4] += curData.abroad_in;
			statistic[5] += curData.asymptomatic;
			statistic[6] += statistic[0] - statistic[1] - statistic[2];

			// 处理省份输入输出
			var ratio = Math.round(statistic[4] / statistic[0] * 100)

			// 处理各省的四个趋势图
			var dates = [], diag_list = [], dead_list = [], cured_list = [], newAddList = [];
			for(var i = 0; i < arr.length; i++){
				dates.push(arr[i]['date']);
				diag_list.push(arr[i]['diagnosed']);
				dead_list.push(arr[i]['dead']);
				cured_list.push(arr[i]['cured']);
			}
			
			// 新增
			for( var i = 1; i < diag_list.length; i++){
				if(i == 0)
					newAddList.push(diag_list[0])
				else
					newAddList.push(diag_list[i] - diag_list[i-1])
			}

			// 传值设定state
			that.setState({
				provinceStatistic: statistic,
				diagnosedList: diag_list,
				deadList: dead_list,
				curedList: cured_list,
				newAddList: newAddList,
				dates: dates,
				ratio: ratio
			}, () => {
				console.log("more info")
			})
		})
	}

	getStatistic = () => {
		let that = this
		var curData = {}
		var json = {}
		console.log("current provinceID: ", this.state.provinceId)
		if(this.state.provinceId == 0)
			json = this.state.json
		else
			json = this.state.json2
		for( var k in json ) {
			curData = json[k]
		}
		// 处理省份六种人数统计
		var statistic = new Array(7).fill(0)
		statistic[0] += curData.diagnosed;
		statistic[1] += curData.dead;
		statistic[2] += curData.cured;
		statistic[3] += curData.suspected;
		statistic[4] += curData.abroad_in;
		statistic[5] += curData.asasymptomatic;
		statistic[6] += statistic[0] - statistic[1] - statistic[2];

		// 处理省份输入输出
		var ratio = Math.round(statistic[4] / statistic[0] * 100)
		
		// 处理各省的四个趋势图
		var dates = [], diagnosedList = [], deadList = [], curedList = [], newAddList = [];
		for( var date in json) {
			dates.push(date);
			diagnosedList.push(json[date].diagnosed);
			deadList.push(json[date].dead);
			curedList.push(json[date].cured);
		}
		// 新增
		for( var i = 0; i < diagnosedList.length; i++){
			if(i == 0)
				newAddList.push(diagnosedList[0])
			else
				newAddList.push(diagnosedList[i] - diagnosedList[i-1])
		}
		// 传值设定state
		that.setState({
			ratio: ratio,
			provinceStatistic: statistic,
			diagnosedList: diagnosedList,
			deadList: deadList,
			curedList: curedList,
			newAddList: newAddList,
			dates: dates
		}, () => {
			console.log("cur state: ", this.state)
		})
	}

	render() {
		return (
			// TODO: 将人群数据替换为真实数据, value
			<Layout>
				<Content style={{ padding: '0 50px' }}>
					<Layout className="site-layout-background" style={{ marginTop: '24px'}}>
						<Layout >
							<Layout className="site-page-header-ghost-wrapper" style={{paddingRight:"20px", paddingBottom:"10px"}}>
								<PageHeader
								ghost={false}
								onBack={() => window.history.back()}
								title="省份疫情数据"
								extra={[
									<Select style={{ width: "120px" }} defaultValue={"北京"} onChange={this.handleChange} >
										{this.state.provinceList.map((item) => {
											return <Option value={item.provinceId}>{item.name}</Option>
											})
										}
									</Select>
								]}
								>
									<Statistics data={this.state.provinceStatistic} />
								</PageHeader>
							</Layout>	
							<Layout style={{paddingRight:"20px", paddingTop:"10px"}} >
								<LineThreeType dates={this.state.dates} cure={this.state.curedList} dead={this.state.deadList} diagnosed={this.state.diagnosedList} />
							</Layout>					
						</Layout>

						<Sider className="site-layout-background" width={400}>
							<Layout className="site-page-header-ghost-wrapper" >
								<PageHeader
								ghost={false}
								title="新增确诊人数趋势"
								>
								</PageHeader>							
							</Layout>	
							<Layout style={{ paddingBottom:"10px"}}>
								<LineOneType dates={this.state.dates} new={this.state.newAddList} />
							</Layout>	
							<Layout style={{ paddingTop:"10px" }}>
								<Gauge data={this.state.ratio} />
							</Layout>
						</Sider>
					</Layout>
				</Content>
				<Footer style={{ textAlign: 'center' }}> ©2020 Created by G7, from course - Foundation Of SE</Footer>
			</Layout>
		)
	}
}

export default SituationMoreInfo