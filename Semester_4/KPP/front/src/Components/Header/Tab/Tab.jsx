import React from "react";
import styles from "./Tab.module.css"


const Tab = ({tab, activeTabId, setActiveTabId}) => {
    const handlerOnClick = (id) => {
        activeTabId.includes(id) ? setActiveTabId(prev => prev.filter(item => item !== id)) : setActiveTabId(prev => [...prev, id]);
    }
    return (
        <div className={styles.tab} onClick={() => handlerOnClick(tab.id)}>
            {tab.tabTitle}
        </div>
    )
}

export default Tab;
