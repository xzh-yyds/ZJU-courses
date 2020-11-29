import React, { Component } from 'react';
import { Row, Statistic } from 'antd';

class Statistics extends Component {
    constructor (props) {
        super(props);
        console.log("props", this.props)
        this.state = {
            data: this.props.data
        };
        var data = this.state.data
        console.log("data statistic:", data)
    }
    render() {
        return (
            <Row>
                <Statistic title="累计确诊" value={this.props.data[0]} style={{margin: '0 45px 0 0'}}/>
                <Statistic title="现有确诊" value={this.props.data[6]} style={{margin: '0 45px'}}/>
                <Statistic title="现有疑似" value={this.props.data[3]} style={{margin: '0 45px'}}/>
                <Statistic title="治愈出院" value={this.props.data[2]} style={{margin: '0 45px'}}/>	
                <Statistic title="死亡" value={this.props.data[1]} style={{margin: '0 45px'}}/>
                <Statistic title="无症状感染" value={this.props.data[5]} style={{margin: '0 45px'}}/>						
                <Statistic title="境外输入" value={this.props.data[4]} style={{margin: '0 0 0 45px'}}/>
            </Row>
        )
    }
}

export default Statistics;
