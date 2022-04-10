import './App.css';
import {useState} from "react";
import Header from "./Components/Header/Header";
import Lab1 from "./Components/Labs/Lab1/Lab1";
import Lab2 from "./Components/Labs/Lab2/Lab2";
import Lab3 from "./Components/Labs/Lab3/Lab3";
import Lab4 from "./Components/Labs/Lab4/Lab4";
import Lab5 from "./Components/Labs/Lab5/Lab5";
import Lab6 from "./Components/Labs/Lab6/Lab6";
import Lab7 from "./Components/Labs/Lab7/Lab7";

function App() {
    const [activeTabId, setActiveTabId] = useState([]);

    const tabs = [{tabTitle: "Lab 1", id: 1}, {tabTitle: "Lab 2", id: 2}, {tabTitle: "Lab 3", id: 3}, {tabTitle: "Lab 4", id: 4}, {tabTitle: "Lab 5", id: 5}, {tabTitle: "Lab 6", id: 6}, {tabTitle: "Lab 7", id: 7}]

    const labs = [<></>, <Lab1/>, <Lab2/>, <Lab3/>, <Lab4/>, <Lab5/>, <Lab6/>, <Lab7/>]

    return (
        <div className="App">
            <Header tabs = {tabs} activeTabId = {activeTabId} setActiveTabId = {setActiveTabId}/>
            {labs.filter((item, index) => activeTabId.includes(index))}
        </div>

   );
} 

export default App;



