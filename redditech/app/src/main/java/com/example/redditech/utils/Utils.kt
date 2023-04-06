package com.example.redditech.utils

object Utils {

    fun formatSubCount(number: Double): String {
        return when {
            number.toInt() < 1000 -> (number.toInt().toString())
            number.toInt() < 1000000 -> {
                val dividedNumber: Double = number / 1000
                ((String.format("%.1f", dividedNumber) + "k").replace(',', '.'))
            }
            else -> {
                val dividedNumber: Double = number / 1000000
                ((String.format("%.1f", dividedNumber) + "M").replace(',', '.'))
            }
        }
    }
}