import React, { Component } from 'react';
import ReactEcharts from 'echarts-for-react';
import {Radio} from 'antd';

class LineThreeType extends Component {
  constructor(props) {
    super(props)
    this.state = {
      value: 1,
    }
  };
  onChange = e => {
    this.setState({
      value: e.target.value
    })
  };
  getOption = () => {
    return {
      backgroundColor: "#fff",
      tooltip: {    // 提示框
        trigger: "axis",
      },
      xAxis: {
        data: this.props.dates
      },
      yAxis: {
        splitLine:{
            show: false
        }
      },
      toolbox: {
          left:  'center',
          feature: {
              dataZoom: {
                  yAxisIndex: 'none'
              },
          } 
      },
      dataZoom: [{
          startValue: this.props.dates[0]
      }, {
          type: 'inside'
      }], 
      series: [
        {
          name: '人数',
          type: 'line',
          data: (this.state.value == 1 ? this.props.cure : (this.state.value == 2 ? this.props.dead : this.props.diagnosed))
        },
      ],
      visualMap: {
        type: "piecewise",
        top: 10,
        right: 10,
        show: true,
        pieces: [
          { min: 10000 },
          { min: 1000, max: 9999 },
          { min: 500, max: 999 },
          { min: 100, max: 499 },
          { min: 10, max: 99 },
          { min: 1, max: 9 },
          { value: 0 }
        ],
        inRange: {
          color: ["#FFFFFF", "#FDEBCA", "#E25552", "#CA2B2D", "#831A26", "#500312"] 
        }
      }
    }
  }
  render() {
    return (
        <div style={{ textAlign:'center', backgroundColor: "#fff" }}>
            <Radio.Group style={{paddingTop:"20px", paddingBottom:"20px"}}  onChange={this.onChange}  value={this.state.value}>
                <Radio value={1}>治愈人数</Radio>
                <Radio value={2}>死亡人数</Radio>
                <Radio value={3}>确诊人数</Radio>
            </Radio.Group>
            <ReactEcharts option={this.getOption()} style={{ height: "510px", paddingBottom:'10px'}}></ReactEcharts> 
        </div>
    )
  }
}

export default LineThreeType;
