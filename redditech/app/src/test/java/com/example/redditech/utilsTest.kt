package com.example.redditech

import com.example.redditech.utils.Utils
import org.junit.Test

import org.junit.Assert.*

class utilsTest {
    @Test
    fun utilsK() {
        val numberOne : String = Utils.formatSubCount(10.0)
        assertEquals("10", numberOne)
    }

    @Test
    fun utilsM() {
        val numberTwo : String = Utils.formatSubCount(10000.0)
        assertEquals("10.0k", numberTwo)
    }

    @Test
    fun utilsInt() {
        val numberThree : String = Utils.formatSubCount(3000000.0)
        assertEquals("3.0M", numberThree)
    }
}