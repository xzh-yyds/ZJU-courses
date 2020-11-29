import React, { Component } from 'react';
import ReactEcharts from 'echarts-for-react';
import { Typography } from 'antd';
const {Title} = Typography;

class Gauge extends Component {
  constructor(props) {
    super(props);
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
          data: [{value: this.props.data, name: '输入占比'}],  
          zoom: 1, // 当前缩放比例
          axisLine: { lineStyle: { width: 20}},
          splitLine: { length: 20 }
        },
      ],
    }
  }
  render() {
    return (
        <div style={{textAlign:'center', backgroundColor:'#fff', paddingTop:'10px'}}>
          <Title level={4}>境内外输入对比</Title>
          <ReactEcharts option={this.getOption()} style={{ height: "300px" }}></ReactEcharts> 
        </div>
    )
  }
}

export default Gauge;
