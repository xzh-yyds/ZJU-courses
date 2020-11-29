import React, { Component } from 'react';
import ReactEcharts from 'echarts-for-react';
import {Radio} from 'antd';

class LineOneType extends Component {
  constructor(props) {
    super(props);
  }
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
          name: 'NewIncreasing',
          type: 'line',
          data: this.props.new,
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
            <ReactEcharts option={this.getOption()} style={{ height: "300px" }}></ReactEcharts> 
        </div>
    )
  }
}

export default LineOneType;
