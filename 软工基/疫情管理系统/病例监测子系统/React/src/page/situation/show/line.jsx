import React, { Component } from 'react';
import ReactEcharts from 'echarts-for-react';
import {Radio} from 'antd';

class LineGraph extends Component {
  constructor(props) {
    super(props);
    this.state = {
      value: 1,
      xData: this.props.dates,
      graphData: this.props.cure
    }
  }
  onChange = e => {
    console.log('radio checked', e.target.value);
    console.log("dates:", this.props.dates)
    this.setState({
      value: e.target.value,
    });
    if( e.target.value == 1){
      this.setState({
        xData: this.props.dates,
        graphData: this.props.cure
      });
    }
    else if( e.target.value == 2){
      this.setState({
        xData: this.props.dates,
        graphData: this.props.dead
      });
    }
    else{
      this.setState({
        xData: this.props.dates,
        graphData: this.props.diagnosed
      });
    }
  };
  getOption = () => {
    return {
      backgroundColor: "#fff",
      tooltip: {    // 提示框
        trigger: "axis",
      },
      xAxis: {
        data: this.state.xData
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
          startValue: this.state.xData[0] 
      }, {
          type: 'inside'
      }], 
      series: [
        {
          name: 'Total_Patients',
          type: 'line',
          data: this.state.graphData,
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
    console.log("render line graph");
    return (
        <div style={{ textAlign:'center', backgroundColor: "#fff" }}>
            <Radio.Group onChange={this.onChange} value={this.state.value}>
                <Radio value={1}>治愈人数</Radio>
                <Radio value={2}>死亡人数</Radio>
                <Radio value={3}>确诊人数</Radio>
            </Radio.Group>
            <ReactEcharts option={this.getOption()} style={{ height: "300px", paddingTop:"10px" }}></ReactEcharts> 
        </div>
    )
  }
}

export default LineGraph;