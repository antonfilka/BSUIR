import React from "react";
import styles from "./CloseButton.module.css"


const CloseButton = ({setActiveTabId}) => {
    const handlerOnClick = () => {
        setActiveTabId([])
    }

    return (
        <div className={styles.button} onClick={() => handlerOnClick()}>
            Close all
        </div>
    )
}

export default CloseButton;
