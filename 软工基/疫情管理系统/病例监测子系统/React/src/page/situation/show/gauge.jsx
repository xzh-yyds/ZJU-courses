import React, { Component } from 'react';
import ReactEcharts from 'echarts-for-react';
import { Radio } from 'antd';

class Gauge extends Component {
  constructor(props) {
    super(props);
    this.state = {
      op: "a",
      value: this.props.cureRatio 
    }
  }

  onChange = e => {
      console.log('radio checked', e.target.value);
      if(e.target.value == 'a'){
        this.setState({
          value:this.props.cureRatio,
          op:"a"
        })
      }
      else{
        this.setState({
          value:this.props.deadRatio,
          op:"b"
        })
      }
  };

  state = {
    gaugeData: []
  }

  getOption = () => {
    return {
      backgroundColor: "#fff",
      tooltip: {    // 提示框
        trigger: "axis",
      },
      series: [
        {
          name: 'Ratio',
          type: 'gauge',
          data: [{value: this.state.value, name: this.state.name}],   
          zoom: 1, // 当前缩放比例
          axisLine: { lineStyle: { width: 20}},
          splitLine: { length: 20 }
        },
      ],
    }
  }
  
  render() {
    console.log("render line graph");
    return (
        <div>
            <Radio.Group onChange={this.onChange} defaultValue={this.state.op}>
                <Radio.Button style={{ width:"200px", height:"50px", textAlign: 'center', lineHeight: "50px" }} value="a">全国治愈率</Radio.Button>
                <Radio.Button style={{ width:"200px", height:"50px", textAlign: 'center', lineHeight: "50px" }} value="b">全国死亡率</Radio.Button>
            </Radio.Group>
            <ReactEcharts option={this.getOption()} style={{ height: "250px" }}></ReactEcharts> 
        </div>
    )
  }
}

export default Gauge;
