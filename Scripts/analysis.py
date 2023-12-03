import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

# Load the data
def load_data():
    data = pd.read_csv('./Data/scheduling_algorithm_performance.csv')
    data['Algorithm'] = data['Algorithm'].replace({'First Come First Serve (non-preemptive)': 'FCFS', 'Round Robin (preemptive)': 'RR'})
    return data

df = load_data()

# Title for the Streamlit app
st.title('Scheduling Algorithms Performance Comparison')

# Function to annotate bars in bar chart
def annotate_bars(ax):
    for bar in ax.patches:
        bar_value = bar.get_height()
        ax.annotate(f'{bar_value:.1f}', 
                     (bar.get_x() + bar.get_width() / 2, bar.get_height()), 
                     ha='center', va='center', 
                     size=8, xytext=(0, 5),
                     textcoords='offset points')

# Function to display styled caption
def styled_caption(text):
    st.markdown(f"<p style='font-size: 16px; font-weight: bold;'>{text}</p>", unsafe_allow_html=True)

# Function to create a bar chart
def create_bar_chart(data, x_col, y_col, ylabel, caption):
    fig, ax = plt.subplots()
    data.plot(kind='bar', x=x_col, y=y_col, ax=ax, color=['blue', 'orange'], legend=False)
    ax.set_ylabel(ylabel)
    ax.set_xticklabels(ax.get_xticklabels(), rotation=0)  # Set x-tick labels horizontally
    annotate_bars(ax)
    st.pyplot(fig)
    styled_caption(caption)

# Average TAT Comparison
st.subheader('Average Turnaround Time (TAT) Comparison')
create_bar_chart(df, 'Algorithm', 'Average TAT', 'Average TAT (time units)', "A lower TAT value indicates better performance.")

# Average Waiting Time Comparison
st.subheader('Average Waiting Time Comparison')
create_bar_chart(df, 'Algorithm', 'Average Waiting Time', 'Average Waiting Time (time units)', "A lower waiting time is preferable, indicating more efficient processing.")

# CPU Efficiency Comparison
st.subheader('CPU Efficiency Comparison')
create_bar_chart(df, 'Algorithm', 'CPU Efficiency', 'CPU Efficiency (%)', "Higher CPU Efficiency percentages are better, indicating optimal CPU usage.")

# Total Time Comparison
st.subheader('Total Time Comparison')
create_bar_chart(df, 'Algorithm', 'Total Time', 'Total Time (time units)', "A lower total time value indicates faster overall algorithm performance.")
