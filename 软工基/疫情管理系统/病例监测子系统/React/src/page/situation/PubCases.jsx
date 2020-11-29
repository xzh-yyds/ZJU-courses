import React, {useState} from 'react';
import $ from 'jquery';
import { Link } from 'react-router-dom';
import { Col, Layout, PageHeader, Row, Statistic, Form, InputNumber, Button, DatePicker, Typography} from 'antd';
import moment from 'moment';
import cookie from 'react-cookies'

const { Content, Footer, Sider } = Layout;
const { Title } = Typography;

class PubCases extends React.Component {	
	state = {
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

		provinceData : {
			0:['北京','BJ'],
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
		today : new Array(6).fill(-2),
		total : new Array(7).fill(-2),
		dayToDel : new Array(6).fill(-2),
		json_today : {
			"prov_name" : "BJ",
			"diagnosed" : 50,
			"dead" : 30,
			"cured" : 10,
			"suspected" : 60,
			"abroad_in" : 61,
			"asymptomatic" : 52,
		},
		json_total : {
			"prov_name" : "BJ",
			"diagnosed" : 523,
			"dead" : 123,
			"cured" : 351,
			"suspected" : 142,
			"abroad_in" : 520,
			"asymptomatic" : 521,
		},
		json_del : {
			"prov_name" : "BJ",
			"new" : "---",
			"diagnosed" : "---",
			"dead" : "---",
			"cured" : "---",
			"suspected" : "---",
			"abroad_in" : '---',
			"asymptomatic" : "---",
		},
		province : "BJ",
		url : "/background/Cases?province=" + "BJ",
	}
	componentWillMount(){

		//console.log(this.props.location)//传递过来的所有参数
		console.log(this.props.location.state.province);
		this.getStatistics();
		this.getRearEnd();
	}

	constructor(props){
		super(props);
		console.log(this.props.location.state)
		var adname = this.props.location.state.adname
		this.setState({
			adminName: adname,
		});

		var provinceId = this.state.nametoID[adname]

		this.setState({
			province : this.state.provinceData[provinceId][0]
		})
		var urlProp = this.state.provinceData[provinceId][1]
		// TODO: 这个url是否正确
		var url = "/background/Cases?province="+urlProp
		this.setState({
			url: url
		})
	}

	getStatistics = () => {
		let that = this;

		var arr = new Array(6).fill(-1);
		var tmp = this.state.json_today;
		arr[0] = tmp['diagnosed'];
		arr[1] = tmp['suspected'];
		arr[2] = tmp['cured'];
		arr[3] = tmp['dead'];
		arr[4] = tmp['asymptomatic'];
		arr[5] = tmp['abroad_in'];
		that.setState({
			today : arr
		})

		arr = new Array(7).fill(-1);
		tmp = this.state.json_total;
		arr[0] = tmp['diagnosed'];
		arr[1] = tmp['suspected'];
		arr[2] = tmp['cured'];
		arr[3] = tmp['dead'];
		arr[4] = tmp['asymptomatic'];
		arr[5] = tmp['abroad_in'];
		arr[6] = arr[0] - arr[2] - arr[3]
		that.setState({
			total : arr
		})

		arr = new Array(6).fill(-1);
		tmp = this.state.json_del;
		arr[0] = tmp['diagnosed'];
		arr[1] = tmp['suspected'];
		arr[2] = tmp['cured'];
		arr[3] = tmp['dead'];
		arr[4] = tmp['asymptomatic'];
		arr[5] = tmp['abroad_in'];
		that.setState({
			dayToDel : arr
		})
	}

	getRearEnd = () => {
		let that = this;

		var province = this.state.province;
		// TODO：以下部分类似于situation里面
		$.ajaxSetup({data: {csrfmiddlewaretoken: '{{ csrf_token}}' }});
		let url_1 = "/background/Cases?province=" + province;
		let url_2 = "/background/Cases?bydate=ture&province=" + province;
		
		// 以下获取今日数据并处理
		$.getJSON(url_2, function(json){
			console.log(json);
			var answer = json;
			var array = answer["array"];

			// 处理全国六种人数统计
			var statistic = new Array(6).fill(0)
			var i = array.length - 1;
			if(i>0){
				statistic[0] = array[i]["diagnosed"] - array[i-1]["diagnosed"];
				statistic[1] = array[i]["suspected"] - array[i-1]["suspected"];
				statistic[2] = array[i]["cured"] - array[i-1]["cured"];
				statistic[3] = array[i]["dead"] - array[i-1]["dead"];
				statistic[4] = array[i]["asymptomatic"] - array[i-1]["asymptomatic"];
				statistic[5] = array[i]["abroad_in"] - array[i-1]["abroad_in"];
				that.setState({
					today: statistic,
				})
			}
		})

		// 以下获取省份数据并处理
		$.getJSON(url_1, function(json){
			console.log(json);
			var answer = json;
			var array = answer["array"];
			// 处理全国六种人数统计
			var statistic = new Array(7).fill(0)
			var i = array.length - 1;
			if(i>=0){
				statistic[0] = array[i]["diagnosed"];
				statistic[1] = array[i]["suspected"];
				statistic[2] = array[i]["cured"];
				statistic[3] = array[i]["dead"];
				statistic[4] = array[i]["asymptomatic"];
				statistic[5] = array[i]["abroad_in"];
				statistic[6] += (statistic[0] - statistic[3] - statistic[2]);
				that.setState({
					total: statistic,
				})
			}
		})
	}

	componentDidMount(){
		//this.getStatistics()
	}

	onDeleted = values => {
		console.log("Delete on: ", values);
		if (window.confirm("确认删除吗?")) {
			// console.log(values.date._d)
			var res = '2020-06-02';
			var res = moment(values.date).format('YYYY-MM-DD');
			var date = res.toString();
			var url = this.state.url
			// 生成json
			// var province = this.state.province
			// var provinceName = this.state.provinceData[province][1]
			var provinceName = this.state.province
			var json = {
				"operation": 1,
				"new_or_total": 0,
				"date": date,
				"province": provinceName,
				"diagnosed": 0,
				"suspected": 0,
				"cured": 0,
				"dead": 0,
				"abroad_in": 0,
				"asymptomatic": 0
			}
			var json_post = JSON.stringify(json);
			console.log(json_post);
			// TODO: 以下请求过程是否正确
			$.ajaxSetup({data: {csrfmiddlewaretoken: '{{ csrf_token}}' }});
			$.post(url, json_post, function(json){

			},"json")
				.done(function(json) {
					var res = json;
					console.log(res);
					var msg = res['msg'];
					var status = res['status']
					alert("消息: " + msg + "\n状态: " + status);
				})
				.fail(function() {
					alert( "error" );
				});
		} 
	};

	onSubmitted = values => {
		console.log("Submit on: ", values)
		if (window.confirm("确认发布吗?")) {
			//var province = this.state.province
			var cure = parseInt(values.cure)
			var nonSymptom = parseInt(values.nonSymptom)
			var death = parseInt(values.death)
			var suspect = parseInt(values.suspect)
			var diag = parseInt(values.diag) // 确诊
			var importNum = parseInt(values.import) // 入口
			var res = moment(values.date).format('YYYY-MM-DD');
			var date = res.toString();
			// 以下发送请求
			var url = this.state.url
			// 生成json
			// var province = this.state.province
			// var provinceName = this.state.provinceData[province][1]
			var provinceName = this.state.province
			var json = {
				"operation": 0,
				"new_or_total": 0,
				"date": date,
				"province": provinceName,
				"diagnosed": diag,
				"suspected": suspect,
				"cured": cure,
				"dead": death,
				"abroad_in": importNum,
				"asymptomatic": nonSymptom
			}
			var json_post = JSON.stringify(json);
			console.log(json_post);
			// TODO: 以下请求过程是否正确
			$.ajaxSetup({data: {csrfmiddlewaretoken: '{{ csrf_token}}' }});
			$.post(url, json_post, function(json){
				
			},"json")
				.done(function(json) {
					var res = json;
					console.log(res);
					var msg = res['msg'];
					var status = res['status']
					alert("消息: " + msg + "\n状态: " + status);
				})
				.fail(function() {
					alert( "error" );
				});
		}
	};

	getDayToDel = values => {
		console.log("delete on: ", values);
		let that = this;
		var del_date = moment(values).format("YYYY-MM-DD");
		console.log("day to del:", del_date);
		var province = this.state.province;
		let url_3 = "/background/Cases?province=" + province+"&date="+del_date;
		$.getJSON(url_3, function(json){
			console.log(json);
			var answer = json;
			var array = answer["array"];
			// 处理全国六种人数统计
			var statistic = new Array(6).fill(0)
			var i = array.length - 1;
			if(i>=0){
				statistic[0] = array[i]["diagnosed"];
				statistic[1] = array[i]["suspected"];
				statistic[2] = array[i]["cured"];
				statistic[3] = array[i]["dead"];
				statistic[4] = array[i]["asymptomatic"];
				statistic[5] = array[i]["abroad_in"];
				that.setState({
					dayToDel : statistic,
				})
			}
		})
	}

	render() {
		return (
			<Layout>
				<Content style={{ padding: '0 15px' }}>
					<Layout style={{ marginTop: '15px'}}>
						<Layout style={{paddingRight:"20px", paddingBottom:"10px"}}>
							<PageHeader ghost={false} title="本省今日疫情数据">
									<Row>
										{/* todo：本省今日发布数据的接口*/}
										<Statistic title="新增确诊" value={this.state.today[0]} style={{margin: '0 45px 0 0'}}/>
										<Statistic title="新增疑似" value={this.state.today[1]} style={{margin: '0 45px'}}/>
										<Statistic title="今日治愈" value={this.state.today[2]} style={{margin: '0 45px'}}/>	
										<Statistic title="新增死亡" value={this.state.today[3]} style={{margin: '0 45px'}}/>
										<Statistic title="无证感染" value={this.state.today[4]} style={{margin: '0 45px'}}/>						
										<Statistic title="境外输入" value={this.state.today[5]} style={{margin: '0 0 0 45px'}}/>
									</Row>
							</PageHeader>
						</Layout>
						<Layout style={{paddingRight:"20px", paddingBottom:"10px"}}>
							<PageHeader ghost={false} title="本省累计疫情数据"
								extra={[
									<div>
										<Link to="/situation/situationMoreInfo">
											<Button style={{marginLeft: "10px"}} key="1" type="primary">更多数据</Button>
										</Link>
									</div>]}>
									<Row>
										{/* todo：本省累计数据的接口 */}
										<Statistic title="累计确诊" value={this.state.total[0]} style={{margin: '0 45px 0 0'}}/>
										<Statistic title="现存确诊" value={this.state.total[6]} style={{margin: '0 45px'}}/>
										<Statistic title="累计疑似" value={this.state.total[1]} style={{margin: '0 45px'}}/>
										<Statistic title="治愈出院" value={this.state.total[2]} style={{margin: '0 45px'}}/>	
										<Statistic title="累计死亡" value={this.state.total[3]} style={{margin: '0 45px'}}/>
										<Statistic title="累计无症状感染" value={this.state.total[4]} style={{margin: '0 45px'}}/>						
										<Statistic title="累计境外输入" value={this.state.total[5]} style={{margin: '0 0 0 45px'}}/>
									</Row>
							</PageHeader>
						</Layout>

						<Layout style={{ paddingRight:"20px"}}>
							<Layout style={{ backgroundColor:'#fff', paddingBottom: "10px", marginTop:"10px", }}>
								<Title level={4} style={{paddingTop:'20px', paddingLeft:'20px'}}>发布数据</Title>
								<Form 
								name="submit-record"
								className="ant-advanced-search-form"
								onFinish={this.onSubmitted}
								style={{ backgroundColor:'#fff', paddingLeft:'15px'}}
							>
							<Row gutter={32}>
								<Col span={5}>
								<Form.Item
									name="date"
									label="选择日期"
									rules={[{required: true}]}>
									<DatePicker />
								</Form.Item>
								</Col>
								<Col span={5}>
								{/*提交数据 */}
								<Form.Item
									name="import"
									label="境外输入"
									rules={[{required: true,}]}>
									<InputNumber value={3}/>
								</Form.Item>
								</Col>
								<Col span={5}>
								<Form.Item
									name="nonSymptom"
									label="无证感染"
									rules={[{required: true,}]}>
									<InputNumber  />
								</Form.Item>
								</Col>
								<Col span={5}>
								<Form.Item
									name="cure"
									label="治愈者"
									rules={[{required: true,}]}>
									<InputNumber />
								</Form.Item>
								</Col>
								<Col span={5}>
								<Form.Item
									name="diag"
									label="确诊患者"
									rules={[{required: true,}]}>
									<InputNumber  />
								</Form.Item>
								</Col>
								<Col span={5}>
								<Form.Item
									name="suspect"
									label="疑似患者"
									rules={[{required: true,}]}>
									<InputNumber  />
								</Form.Item>
								</Col>
								<Col span={5}>
								<Form.Item
									name="death"
									label="死亡患者"
									rules={[{required: true,}]}>
									<InputNumber  />
								</Form.Item>
								</Col>
							</Row>
							<Row>
								<Col span={21} style={{ textAlign: 'right' }}>
								<Button type="primary" htmlType="submit">
									提交
								</Button>
								</Col>
							</Row>
							</Form>
							</Layout>	
						</Layout>
						
						<Layout style={{ paddingRight:"20px"}}>
							<Layout style={{ backgroundColor:'#fff', paddingBottom: "10px", marginTop:"10px", }}>
							<Title level={4} style={{paddingTop:'20px', paddingLeft:'20px'}}> 删除数据 </Title>
							<Form 
								name="delete-record"
								className="ant-advanced-search-form"
								onFinish={this.onDeleted}
								style={{ backgroundColor:'#fff', paddingLeft:'15px'}}
							>
							<Form.Item
								name="date"
								label="选择日期"
								rules={[{required: true}]}>
								<DatePicker onChange={this.getDayToDel}/>
							</Form.Item>
							<Row gutter={16}>
								{/*todo: 根据所选日期，填充病例信息*/}
								<Col span={3}>
								<Statistic title="新增确诊" value={this.state.dayToDel[0]} />
								</Col>
								<Col span={3}>
								<Statistic title="新增疑似" value={this.state.dayToDel[1]} />
								</Col>
								<Col span={3}>
								<Statistic title="今日治愈" value={this.state.dayToDel[2]} />
								</Col>
								<Col span={3}>
								<Statistic title="今日死亡" value={this.state.dayToDel[3]} />
								</Col>
								<Col span={3}>
								<Statistic title="无证感染" value={this.state.dayToDel[4]} />
								</Col>
								<Col span={3}>
								<Statistic title="境外输入" value={this.state.dayToDel[5]} />
								</Col>
							</Row>
							<Row>
								<Col span={21} style={{ textAlign: 'right' }}>
								<Button type="primary" htmlType="submit">
									删除
								</Button>
								</Col>
							</Row>
							</Form>
							</Layout>
						</Layout>			

					</Layout>
				</Content>
				<Footer style={{ textAlign: 'center' }}> ©2020 Created by G7, from course - Foundation Of SE</Footer>
			</Layout>
		)
	}
}

export default PubCases