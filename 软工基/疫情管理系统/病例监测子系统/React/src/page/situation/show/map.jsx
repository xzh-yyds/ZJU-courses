import React, { Component } from 'react';
import ReactEcharts from 'echarts-for-react';

import jsonp from "jsonp" // 接口jsonp实现跨域
import "../../../utils/china"


class Map extends Component {
  constructor(props) {
    super(props);
    this.state = {
      mapData: this.props.data
    }
    console.log("map data: ", this.state.mapData)
  }
  getOption = () => {
    return {
      backgroundColor: "#fff",
      tooltip: { // 提示框
        trigger: "item",
        formatter: "省份: {b} <br/> 现有确诊：{c}" // a 系列名称 b 区域名称 c 合并数值
      },
      series: [
        {
          type: 'map',
          map: "china",
          data: this.props.data,
          label: {
            show: true,
            color: "black",
            fontStyle: 10,
            align: "center"
          },
          zoom: 1, // 当前缩放比例
          roam: true, // 是否支持拖拽
          itemStyle: {
            borderColor: "blue", // 区域边框线
          },
          emphasis: { // 高亮显示
            label: {
              color: "black",
              fontSize: 10
            },
            itemStyle: {
              areaColor: "lightyellow" // 区域高亮颜色
            }
          }
        },
      ],
      visualMap: {
        type: "piecewise",
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
    console.log("render");
    return (
        <ReactEcharts option={this.getOption()} style={{ height: "550px" }}></ReactEcharts> 
    )
  }
}

export default Map