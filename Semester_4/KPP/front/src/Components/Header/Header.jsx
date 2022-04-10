import React from "react";
import styles from "./Header.module.css"
import Tab from "./Tab/Tab";
import CloseButton from "./CloseButton/CloseButton";


const Header = ({tabs, activeTabId, setActiveTabId}) => {
    return (
        <div className={styles.header}>
            {tabs.map(tab => <Tab tab={tab} activeTabId={activeTabId} setActiveTabId={setActiveTabId}/>)}
           <CloseButton setActiveTabId={setActiveTabId}/>
        </div>
    )
}

export default Header;
