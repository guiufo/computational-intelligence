#=
Program to solve the "send + more = money" problem
Each individual is a row in a 180 x 11 matrix
Positions 1 to 10 is for the permutation
The individual is the positions from 1 to 8
The order of the row is "sendmoryXY"
XY holds digits to facilitate crossover and mutation
=#
using StatsBase
include("MyModule.jl")

"Evaluate individuals"
function evaluate(problem, m)
	a, b, c = split(problem, r"\+|\=")
	x = *(a,b,c)
	y = ""

	for i in 1:size(x)
		if !contains(y,x[i:i])
			y = *(y,x[i:i])
		end
	end

	for i in 1:MSIZE
		send = more = money = 0
		send = m[i,1]*1000+m[i,2]*100+m[i,3]*10+m[i,4]
		more = m[i,5]*1000+m[i,6]*100+m[i,7]*10+m[i,2]
		money = m[i,5]*10000+m[i,6]*1000+m[i,3]*100+m[i,2]*10+m[i,8]
		m[i,end] = abs(send + more - money)
	end

	return m
end

function initPopulation(populationSize, problem, m)
	a, b, c = split(problem, r"\+|\=")
	x = *(a,b,c)
	y = ""

	for i in 1:size(x)
		if !contains(y,x[i:i])
			y = *(y,x[i:i])
		end
	end
end
		

function randomMatrix(m)
	for i in 1:size(m,2)
		m[i,1:end-1] = sample(0:9, 10, replace=false)
	end
	return m
end

"Make a roulette and select 80 individuals"
function roulette(m)
	fitnessSum = sum(m[1:100,end])
	pSum = 0.0
	rouletteValues = zeros(Float64,100)
	# mount the roulette
	for i in 1:100
		rouletteValues[i] = pSum + (m[i,end]/fitnessSum)
		pSum += rouletteValues[i]
	end

	for i in 101:180
		spin = rand()*pSum
		selected = 1
		for j in 1:99
			if spin > rouletteValues[j] && spin <= rouletteValues[j+1]
				selected = j
				break
			end
		end
		m[i,:] = m[selected,:]
	end
	return m
end


function tournament(m)
	for i in POPSIZE+1:MSIZE
		best = BIGNUMBER
		bestIndex = 1 
		for j in 1:TOUR
			randInt = rand(1:POPSIZE)
			if m[randInt,end] < best
				best = m[randInt,end]
				bestIndex = randInt
			end	
		end	
		m[i,:] = m[bestIndex,:]
	end
	return m
end

"Makes a cyclic crossover in selected fathers"
function cyclicCrossover(m)
	for i in POPSIZE+1:POPSIZE-1
		tempIndex = rand(1:10)
		initialValue = m[i,tempIndex]
		while m[i+1,tempIndex] != initialValue
			nextValue = m[i+1,tempIndex]
			
			m[i+1,tempIndex],m[i,tempIndex] = m[i,tempIndex],m[i+1,tempIndex]

			for j in 1:10
				if j != tempIndex && m[i,j] == nextValue
					tempIndex = j
					break
				end
			end
		end
		# Make the last swap, closing the cycle
		m[i+1,tempIndex],m[i,tempIndex] = m[i,tempIndex],m[i+1,tempIndex]
	end
	return m
end

function mutation(m)
	for i in POPSIZE:size(m,1)
		randRow = rand(POPSIZE:MSIZE)
		randColumn = rand(1:PROBLEMSIZE)
		randXY = rand(1:10)
		m[randRow,randColumn],m[randRow,randXY] = m[randRow,randXY],m[randRow,randColumn] 
	end
	return m
end

function run1()
	run(100, 100, 200, 80, 10)
end

function run(NEXPERIMENTS, POPSIZE, NGENERATIONS, CROSS, MUTATION)
	MSIZE = POPSIZE + POPSIZE * CROSS
	TOUR = 3
	counter = 0
	for i in 1:NEXPERIMENTS
		m = zeros(Int32,MSIZE,11)
		m = randomPopulation(m)
		m = evaluate(m)

		for j in 1:NGENERATIONS
			m = tournament(m)
			m = cyclicCrossover(m)
			m = mutation(m)
			m = evaluate(m)
			m = sortrows(m, by=x->x[end])
			if m[1,end] == 0
				counter += 1
				break
			end
		end

	end
	@printf("%s experiments and %s generations:\n", NEXPERIMENTS, NGENERATIONS)
	@printf("%2.1f%% of sucess\n", (counter/NEXPERIMENTS)*100)
	return
end
=#
