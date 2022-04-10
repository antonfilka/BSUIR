import React from "react";
import styles from "./Represent.module.css"


const Represent = ({activeTabId}) => {

    return (
        <div className={styles.represent} >
            {activeTabId.map(item => item)}
        </div>
    )
}

export default Represent;
